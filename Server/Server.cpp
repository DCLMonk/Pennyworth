/*
 * Server.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Server.h"
#include <errno.h>
#include "Comm/SocketCreator.h"
#include "Comm/SerialComm.h"
#include "Comm/SocketComm.h"
#include <fcntl.h>

namespace dvs {

vector<Room*> rooms;
unsigned int maxUserId = 0;
queue<unsigned int> availableIds;
map<unsigned int, User*> users;

Server::Server() {

}

Server::~Server() {

}

void Server::addListener(int fd, Runnable* listener) {
	fcntl(fd, F_SETFL, O_NONBLOCK);
	fds.push_back(fd);
	readListeners.push_back(listener);
}

void Server::remListener(int fd) {
	for (unsigned int i = 0; i < fds.size(); i++) {
		if (fds[i] == fd) {
			printf("Removing FD: %d\n", fds[i]);
			fds.erase(fds.begin() + i);
			delete readListeners[i];
			readListeners.erase(readListeners.begin() + i);
			return;
		}
	}
}

int is_valid_fd(int fd) {
	return fcntl(fd, F_GETFL) != -1 || errno != EBADF;
}

void Server::run() {
	while (1) {
		int max = 0;
		FD_ZERO(&fdSet);

		for (unsigned int i = 0; i < fds.size(); i++) {
			FD_SET(fds[i], &fdSet);
			if (fds[i] + 1 > max) {
				max = fds[i] + 1;
			}
		}

		int ret = select(max, &fdSet, NULL, NULL, NULL);

		if (ret <= 0) {
			perror("Error with Select");
			if (errno == EPIPE) {
				for (unsigned int i = 0; i < fds.size(); i++) {
					if (FD_ISSET(fds[i], &fdSet)) {
						printf("Removing FD: %d\n", fds[i]);
						delete readListeners[i];
						fds.erase(fds.begin() + i);
						readListeners.erase(readListeners.begin() + i);
						break;
					}
				}
			}
		}
		for (unsigned int i = 0; i < fds.size(); i++) {
			if (FD_ISSET(fds[i], &fdSet)) {
				readListeners[i]->run();
			}
		}
	}
}

} /* namespace dvs */
