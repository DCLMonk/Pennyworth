/*
 * CCommunicator.cpp
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#include "CCommunicator.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include "CPacket.h"

namespace dvs {

CCommunicator::CCommunicator() {
	index = 0;
	user = NULL;
}

CCommunicator::~CCommunicator() {
	if (user != NULL) {
		delete user;
		user = NULL;
	}
}

void CCommunicator::sendPacket(CPacket* packet) {
	string pstring = packet->toString();
	this->writeBytes(pstring.c_str(), pstring.size());
}

void CCommunicator::getPacket() {
	int amount = this->readBytes(buffer + index, BUF_LENGTH - index);
	if (amount > 0) {
		index += amount;
		for (unsigned int i = 0; i < index; i++) {
			pbuffer[i] = buffer[i];
			if (buffer[i] == '\n') {
				pbuffer[i+1] = '\0';
				string packet(pbuffer);
				makePacket(packet);
				for (unsigned int j = i+1; j < index; j++) {
					buffer[j-(i+1)] = buffer[j];
				}
				index -= i + 1;
				break;
			}
		}
	}
}

void CCommunicator::writeBytes(const char* data, unsigned int length) {
	printf("Warning: Unimplemented CCommunicator in Use\n");
}

int CCommunicator::readBytes(char* data, unsigned int length) {
	printf("Warning: Unimplemented CCommunicator in Use\n");
	return -1;
}

void makeLoginPacket(string packet) {
	LoginPacket p(packet);
}

void makeUIDPacket(string packet) {
//	UIDPacket p(packet);
}

void makeLoginFailedPacket(string packet) {
	LoginFailurePacket p(packet);
}

void CCommunicator::makePacket(std::string packet) {
	string ids = packet.substr(0, packet.find(':'));
	int id = atoi(ids.c_str());

	switch (id) {
	case LOGIN:
		makeLoginPacket(packet);
		break;
	case UID:
		makeUIDPacket(packet);
		break;
	case LOGIN_FAILED:
		makeLoginFailedPacket(packet);
		break;
	}
}

}
