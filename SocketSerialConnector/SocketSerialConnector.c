
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <getopt.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#define error perror



int main(int argc, char **argv) {
	struct termios tc; // terminal control structure
	int sockfd, fd;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	const char* host = "localhost";
	int port = 5011;
	int devices =2;
	const char* serial = "/dev/ttyUSB0";
	int i, d;
	char buf[4];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	server = gethostbyname(host);
	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(port);
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");

	fd = open(serial, O_RDWR | O_NOCTTY); // really ought to check for error
	tcgetattr(fd, &tc);
	cfmakeraw(&tc);
    tc.c_iflag = IGNPAR;
    tc.c_oflag = 0;
    tc.c_cflag = CS8 | CREAD | CLOCAL; //8 bit chars enable receiver no modem status lines
    tc.c_lflag =0 ;

	//todo baud rate should not be hard coded
	cfsetispeed(&tc, B9600);
	cfsetospeed(&tc, B9600);
	//todo should have bits per character set
	tcsetattr(fd, TCSANOW, &tc);

	fcntl(sockfd, F_SETFL, O_NONBLOCK);

//	buf[0] = 3;
//	buf[1] = 0;
//	buf[2] = 0;
//	buf[3] = 0;
//	write(fd, buf, 4);
	printf("Connected!\n");
	while (1) {
		if (read(sockfd, buf, 1) > 0) {
			int l = buf[0];
			write(fd, buf, 1);
			printf("Server Sent %d!\n", l);
			for (i = 0; i < l; i++) {
				if (read(sockfd, buf, 1) > 0) {
					write(fd, buf, 1);
				} else {
					i--;
				}
			}
		}
		for (d = 2; d <= devices; d++) {
			buf[0] = '\0';
			buf[1] = d;
			write(fd, buf, 2);
			read(fd, buf, 1);
			if (buf[0] > 0) {
				int l = buf[0];
				printf("Device Sent %d!\n", l);
				write(sockfd, buf, 1);
				for (i = 0; i < l; i++) {
					if (read(fd, buf, 1) > 0) {
						write(sockfd, buf, 1);
					} else {
						i--;
					}
				}
			} else {
				printf("Device Sent %d!\n", buf[0]);
			}
		}
	}

	return 0;
}
