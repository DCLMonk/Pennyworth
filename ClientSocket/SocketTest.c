/*
 * SocketTest.c
 *
 *  Created on: Jun 19, 2012
 *      Author: jmonk
 */
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include "lib/DeviceClient.h"

int sockfd;

void sendch(char c);

int main(int argc, char * argv[]) {
	int portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer;

	portno = 5014;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	server = gethostbyname("localhost");
	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");

	Device* device = createDevice("Test Device", 5, sendch);

	setDeviceCName("Common Name", device);
	setDeviceLocation(0, 0, 0, 0, device);

	addField(type, "Test Bool", 0, 0, 0, device);

	while (1) {
		if (read(sockfd, &buffer, 1) > 0) {
			recvChar(buffer, device);
		}
	}

	return 0;
}

void sendch(char c) {
	write(sockfd, &c, 1);
}
