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
	id = 0;
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
				i = 0;
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

void CCommunicator::makePacket(std::string packet) {
	string ids = packet.substr(0, packet.find(':'));
	int id = atoi(ids.c_str());
	CPacket* p;

	switch (id) {
	case LOGIN:
		p = NULL;
		break;
	case UID:
		p = new UIDPacket(packet, this);
		break;
	case LOGIN_FAILED:
		p = new LoginFailurePacket(packet, this);
		break;
	case GET_DEVICES:
		p = NULL;
		break;
	case DEVICE_DEF:
		p = new DeviceDefPacket(packet, this);
		break;
	case GET_FIELDS:
		p = NULL;
		break;
	case FIELD_INFO:
		p = new FieldInfoPacket(packet, this);
		break;
	case GET_FIELD:
		p = NULL;
		break;
	case SEND_FIELD:
		p = new SendFieldPacket(packet, this);
		break;
	case SET_FIELD:
		p = NULL;
		break;
	case COMMAND:
		p = NULL;
		break;
	}

	if (p != NULL) {
		this->callback(id, p);
		delete p;
	}
}

unsigned int CCommunicator::getId() {
	return id;
}

void CCommunicator::setId(int id) {
	this->id = id;
}

void CCommunicator::callback(int id, CPacket* packet) {
	for (unsigned int i = 0; i < listeners.size(); i++) {
		if (listeners[i]->packetType == id) {
			if (listeners[i]->listener(packet, listeners[i]->data)) {
				listeners.erase(listeners.begin() + i);
				i--;
			}
		}
	}
}

void CCommunicator::registerListener(CPacketTypes type, void* data, Listener listener) {
	listeners.push_back(new PacketListener(type, data, listener));
}

}
