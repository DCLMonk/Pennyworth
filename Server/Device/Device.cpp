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
 * Device.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Device.h"
#include "Communicator.h"
#include "Packet.h"

using namespace std;

namespace dvs {

map<int, Device*> devicesById;
map<string, Device*> devicesByString;
unsigned int maxDeviceId = 1;

Device::Device(Communicator* comm, string name) {
	fields = new map<unsigned char, Field*>;
	deviceId = Device::allocateDeviceId();
	Device::setDevice(deviceId, name, this);
	this->name = name;
	this->comm = comm;
	this->cname = "Unset";
	roomId = -1;
	maxField = 0;
	maxLength = 256;
}

Device::~Device() {

}

unsigned int Device::getId() {
	return deviceId;
}

string Device::getName() {
	return name;
}

string Device::getCName() {
	return cname;
}

void Device::setCName(string cname) {
	this->cname = cname;
}

void Device::send(Packet* packet) {
	comm->sendPacket(packet);
}

Room* Device::getRoom() {
	if (roomId >= 0) {
		return Server::getRoom(roomId);
	} else {
		return NULL;
	}
}

void Device::setRoom(unsigned int roomId) {
	if (this->roomId >= 0) {
		Server::getRoom(this->roomId)->remDevice(this);
	}
	this->roomId = roomId;
	if (this->roomId >= 0) {
		Server::getRoom(this->roomId)->addDevice(this);
	}
}

void Device::setLoc(float x, float y) {
	this->x = x;
	this->y = y;
}

void Device::setIcon(unsigned int icon) {
	this->icon = icon;
}

bool Device::hasField(unsigned char id) {
	return (*fields)[id] != NULL;
}

Field* Device::getField(unsigned char id) {
	return (*fields)[id];
}

void Device::setField(unsigned char id, Field* field) {
	if (hasField(id)) {
		delete ((*fields)[id]);
	}
	if (id + (unsigned int)1 > maxField) {
		maxField = id + 1;
	}
	(*fields)[id] = field;
}

void Device::setComm(Communicator* comm) {
	this->comm = comm;
}

int Device::getNFields() {
	return fields->size();
}

Communicator* Device::getComm() {
	return comm;
}

unsigned int Device::getMaxField() {
	return maxField;
}

unsigned int Device::getIcon() {
	return icon;
}

float Device::getX() {
	return x;
}

float Device::getY() {
	return y;
}

} /* namespace DVS */
