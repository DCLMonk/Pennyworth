/*
 * SocketTest.c
 *
 *  Created on: Jun 19, 2012
 *      Author: jmonk
 */
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
#include <getopt.h>
#include <string.h>
#define error perror

using namespace std;

int sockfd;

void sendch(char c);
void sendField(Device* device, FieldDef* field);

#define DEFAULT_PORT 5010

char* optString = "p:d:u:c:h";

static const struct option longOpts[] = {
	{ "port", required_argument, NULL, 'p' },
	{ "uname", required_argument, NULL, 'u' },
	{ "cname", required_argument, NULL, 'c' },
};

int main(int argc, char * argv[]) {
	int portno;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer;
	char *uname = "Test Device";
	char *cname = "Common Name";

	portno = DEFAULT_PORT;
	int longIndex;
	int opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	while (opt != -1) {
		switch (opt) {
		case 'u':
			uname = optarg;
			break;
		case 'c':
			cname = optarg;
			break;
		case 'p':
			if (optarg == NULL) {
				printf("NULL\n");
			} else {
				printf("Port: %d\n", atoi(optarg));
				portno = atoi(optarg);
			}
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

	Device* device = createDevice(uname, 5, sendch);

	setDeviceCName(cname, device);
	setDeviceLocation(0, 0, 0, 0, device);

	addField(BOOL, "First Field", 0, 1, 0, device);
	addField(INT, "Second Field", 1, 1, 0, device);
	addField(FIXED, "Third Field", 2, 1, 0, device);

	setOneVal(2, 0x0800, device);

	addField(STRING, "Fourth Field", 3, 1, 0, device);

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
