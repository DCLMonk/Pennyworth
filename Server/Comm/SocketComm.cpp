/*
 * SocketComm.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */
#include "SocketComm.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

namespace dvs {

SocketComm::SocketComm(int fd) {
	this->fd = fd;
	fcntl(fd, F_SETFL, O_NONBLOCK);
	StartPacket p;
	sendPacket(&p);
}

SocketComm::~SocketComm() {
	close(fd);
}

void SocketComm::sendPacket(Packet* packet) {
	printf("Socket Write: %d\n", packet->getLength());
	write(fd, packet->getData(), packet->getLength());
}

Packet* SocketComm::getPacket() {
	if (index == 0) {
		int rd = read(fd, buffer, 1);
		if (rd > 0) {
			printf("Start: %d\n", buffer[0]);
			size = buffer[0];
			index = 1;
		}
	} else {
		int rd = read(fd, buffer + index, 1 + size - index);
		if (rd > 0) {
			printf("Read: %d\n", rd);
			index += rd;
			if (index == size + 1) {
				makePacket();
				index = 0;
			}
		}
	}
	return NULL;
}

} /* namespace dvs */
