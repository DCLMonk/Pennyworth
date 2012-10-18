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
		perror("ERROR copening socket");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		perror("ERROR on cbinding");
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
