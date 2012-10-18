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
	stringstream ss(stringstream::out);

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

