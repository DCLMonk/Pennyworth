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
	printf("No More Comm :(\n");
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
				pbuffer[i] = '\0';
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

void makeGetDevicesPacket(string packet) {
	GetDevicesPacket p(packet);
}

void makeDeviceDefPacket(string packet) {
//	DeviceDefPacket p(packet);
}

void makeGetFieldsPacket(string packet) {
	GetFieldsPacket p(packet);
}

void makeFieldInfoPacket(string packet) {
//	FieldInfoPacket p(packet);
}

void makeCommandPacket(string packet) {
	CCommandPacket p(packet);
}

void makeSetFieldPacket(string packet) {
	CSetFieldPacket p(packet);
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
	case GET_DEVICES:
		makeGetDevicesPacket(packet);
		break;
	case DEVICE_DEF:
		makeDeviceDefPacket(packet);
		break;
	case GET_FIELDS:
		makeGetFieldsPacket(packet);
		break;
	case FIELD_INFO:
		makeFieldInfoPacket(packet);
		break;
	case COMMAND:
		makeCommandPacket(packet);
		break;
	case SET_FIELD:
		makeSetFieldPacket(packet);
		break;
	}
}

}
