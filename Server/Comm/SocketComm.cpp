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
#include <errno.h>
#include "../Runnable.h"

namespace dvs {

SocketComm::SocketComm(int fd) {
	this->fd = fd;
	fcntl(fd, F_SETFL, O_NONBLOCK);
	StartPacket p;
	sendPacket(&p);
	server.addListener(fd, new CommHandler(this));
}

SocketComm::~SocketComm() {
	close(fd);
	for (unsigned int i = 1; i < maxDeviceId; i++) {
		Device* device = Device::getDevice(i);
		if (device->getComm() == this) {
			Device::remDevice(i);
			delete device;
		}
	}
}

void SocketComm::sendPacket(Packet* packet) {
	if (write(fd, packet->getData(), packet->getLength()) < 0) {
		if (errno == EPIPE) {
			server.remListener(fd);
		}
	}
}

Packet* SocketComm::getPacket() {
	if (index == 0) {
		int rd = read(fd, buffer, 1);
		if (rd > 0) {
			size = buffer[0];
			index = 1;
		} else if (rd < 0) {
			if (errno == EPIPE) {
				server.remListener(fd);
			} else {
				printf("Other\n");
			}
		}
	} else {
		int rd = read(fd, buffer + index, 1 + size - index);
		if (rd > 0) {
			index += rd;
			if (index == size + 1) {
				makePacket();
				index = 0;
			}
		} else if (rd < 0) {
			if (errno == EPIPE) {
				server.remListener(fd);
			} else {
				printf("Other\n");
			}
		}
	}
	return NULL;
}

} /* namespace dvs */
