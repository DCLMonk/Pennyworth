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
}

CCommunicator::~CCommunicator() {
	printf("No More Comm :(\n");
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

void makeLoginPacket(string packet, CCommunicator* comm) {
//	LoginPacket p(packet, comm);
}

void makeUIDPacket(string packet, CCommunicator* comm) {
	UIDPacket p(packet, comm);
}

void makeLoginFailedPacket(string packet, CCommunicator* comm) {
	LoginFailurePacket p(packet, comm);
}

void makeGetDevicesPacket(string packet, CCommunicator* comm) {
//	GetDevicesPacket p(packet, comm);
}

void makeDeviceDefPacket(string packet, CCommunicator* comm) {
	DeviceDefPacket p(packet, comm);
}

void makeGetFieldsPacket(string packet, CCommunicator* comm) {
//	GetFieldsPacket p(packet, comm);
}

void makeFieldInfoPacket(string packet, CCommunicator* comm) {
	FieldInfoPacket p(packet, comm);
}

void makeGetFieldPacket(string packet, CCommunicator* comm) {
//	GetFieldPacket p(packet, comm);
}

void makeSendFieldPacket(string packet, CCommunicator* comm) {
	SendFieldPacket p(packet, comm);
}

void makeSetFieldPacket(string packet, CCommunicator* comm) {
//	CSetFieldPacket p(packet, comm);
}

void makeCommandPacket(string packet, CCommunicator* comm) {
//	CCommandPacket p(packet, comm);
}

void CCommunicator::makePacket(std::string packet) {
	string ids = packet.substr(0, packet.find(':'));
	int id = atoi(ids.c_str());

	switch (id) {
	case LOGIN:
		makeLoginPacket(packet, this);
		break;
	case UID:
		makeUIDPacket(packet, this);
		break;
	case LOGIN_FAILED:
		makeLoginFailedPacket(packet, this);
		break;
	case GET_DEVICES:
		makeGetDevicesPacket(packet, this);
		break;
	case DEVICE_DEF:
		makeDeviceDefPacket(packet, this);
		break;
	case GET_FIELDS:
		makeGetFieldsPacket(packet, this);
		break;
	case FIELD_INFO:
		makeFieldInfoPacket(packet, this);
		break;
	case GET_FIELD:
		makeGetFieldPacket(packet, this);
		break;
	case SEND_FIELD:
		makeSendFieldPacket(packet, this);
		break;
	case SET_FIELD:
		makeSetFieldPacket(packet, this);
		break;
	case COMMAND:
		makeCommandPacket(packet, this);
		break;
	}
}

unsigned int CCommunicator::getId() {
	return id;
}

void CCommunicator::setId(int id) {
	this->id = id;
}

}
