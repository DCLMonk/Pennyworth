/*
 * CSocketCreator.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */
#include "CSocketCreator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

namespace dvs {

CSocketCreator::CSocketCreator(int port) {
	struct sockaddr_in serv_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("ERROR opening socket");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		perror("ERROR on binding");
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
}

CSocketCreator::~CSocketCreator() {
	close(sockfd);
}

CSocketComm* CSocketCreator::checkConnections() {
	int fd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if (fd >= 0) {
		fcntl(sockfd, F_SETFL, O_NONBLOCK);
		return new CSocketComm(fd);
	}
	return NULL;
}

int CSocketCreator::getFd() {
	return sockfd;
}

}
