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

SocketComm::SocketComm() {

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

void SocketComm::writeBytes(unsigned char* data, unsigned int length) {
	if (write(fd, (const void*)data, (size_t)length) < 0) {
		if (errno == EPIPE) {
			server.remListener(fd);
		}
	}
}

int SocketComm::readBytes(unsigned char* data, unsigned int length) {
	int ret;
	if ((ret = read(fd, data, length)) < 0) {
		if (errno == EPIPE) {
			server.remListener(fd);
		} else {
			printf("Other\n");
		}
	}
	return ret;
}

} /* namespace dvs */
