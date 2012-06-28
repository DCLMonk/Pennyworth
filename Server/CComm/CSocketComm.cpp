/*
 * SocketComm.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */
#include "CSocketComm.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "../Runnable.h"
#include "Server.h"

namespace dvs {

CSocketComm::CSocketComm(int fd) {
	this->fd = fd;
	fcntl(fd, F_SETFL, O_NONBLOCK);

	server.addListener(fd, new CCommHandler(this));
}

CSocketComm::CSocketComm() {

}

CSocketComm::~CSocketComm() {
	close(fd);
	this->CCommunicator::~CCommunicator();
}

void CSocketComm::writeBytes(const char* data, unsigned int length) {
	if (write(fd, (const void*)data, (size_t)length) < 0) {
		if (errno == EPIPE) {
			server.remListener(fd);
		}
	}
	fsync(fd);
}

int CSocketComm::readBytes(char* data, unsigned int length) {
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
