/**
 * Pennyworth - A new smarthome protocol.
 * Copyright (C) 2012  Dream-Crusher Labs LLC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <fcntl.h>
#include <netdb.h>
#include <getopt.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#define error perror

const char* optString = "p:d:n:s:d:h";

static const struct option longOpts[] = {
	{ "port", required_argument, NULL, 'p' },
	{ "host", required_argument, NULL, 'n' },
	{ "numDevices", required_argument, NULL, 'd' },
	{ "serialPort", required_argument, NULL, 's' },
};

int main(int argc, char **argv) {
	struct termios tc; // terminal control structure
	int sockfd, fd;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	const char* host = "localhost";
	int port = 5010;
	int devices = 2;
	const char* serial = "/dev/ttyACM0";
	int i, d;
	char buf[4];
	fd_set fdSet;

	int longIndex;
	int opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	while (opt != -1) {
		switch (opt) {
		case 'n':
			host = optarg;
			break;
		case 'p':
			if (optarg == NULL) {
				printf("NULL\n");
			} else {
				printf("Port: %d\n", atoi(optarg));
				port = atoi(optarg);
			}
			break;
		case 'd':
			devices = atoi(optarg);
			break;
		case 's':
			serial = optarg;
			break;
		default:
			/* You won't actually get here. */
			break;
		}

		opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	}

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
    tc.c_iflag |= IGNCR;
//    tc.c_oflag = 0;
//    tc.c_cflag = CS8 | CREAD | CLOCAL; //8 bit chars enable receiver no modem status line s
//    tc.c_lflag =0 ;

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
	FD_ZERO(&fdSet);
	FD_SET(fd, &fdSet);
	while (1) {
		if (read(sockfd, buf, 1) > 0) {
			int l = buf[0];
			write(fd, buf, 1);
			printf("Server: %d\n", l);
			for (i = 0; i < l; i++) {
				if (read(sockfd, buf, 1) > 0) {
					write(fd, buf, 1);
				} else {
					i--;
				}
			}
		}
		for (d = 1; d <= devices; d++) {
			buf[0] = '\0';
			buf[1] = d;
			write(fd, buf, 2);
			struct timeval tv = {0, 250000};
			if (select(fd + 1, &fdSet, NULL, NULL, &tv)) {
				if (FD_ISSET(fd, &fdSet)) {
					read(fd, buf, 1);
					if (buf[0] > 0) {
						int l = buf[0];
						printf("Device: %d %d\n", d, l);
						write(sockfd, buf, 1);
						for (i = 0; i < l; i++) {
							if (read(fd, buf, 1) > 0) {
								write(sockfd, buf, 1);
							} else {
								i--;
							}
						}
					}
				}
			}
		}
	}

	return 0;
}
