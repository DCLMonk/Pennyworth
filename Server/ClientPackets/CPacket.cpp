/*
 * CPacket.cpp
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */
#include <stdio.h>
#include <stdlib.h>
#include "CPacket.h"
#include "Util.h"
#include "Server.h"

namespace dvs {

CCommunicator* currentCCommunicator = NULL;

CPacket::CPacket(string data) {
	this->args = Util::split(data, ':');
	this->id = atoi((*args)[0].c_str());
	this->user = Server::getUser(atoi((*args)[1].c_str()));
}

CPacket::CPacket(unsigned int id, User* user) {
	this->user = user;
	this->id = id;
	this->args = NULL;
}

CPacket::~CPacket() {
	if (this->args != NULL) {
		delete this->args;
	}
}

string CPacket::toString() {
	stringstream ss(stringstream::in);

	ss << id;
	ss << ':';
	if (user != NULL) {
		ss << user->getId();
	} else {
		ss << 0;
	}

	this->streamData(ss);

	ss << endl;

	return ss.str();
}

void CPacket::streamData(stringstream& data) {
	printf("Warning: Unimplemented streamData in CPacket\n");
}

void CPacket::send() {
	user->send(this);
}

}

