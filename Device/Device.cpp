/*
 * Device.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Device.h"
#include "../Comm/Communicator.h"
#include "../Packets/Packet.h"

namespace dvs {

map<int, Device*> devicesById;
map<string, Device*> devicesByString;

Device::Device(Communicator* comm, string name) {
	deviceId = Device::allocateDeviceId();
	Device::setDevice(deviceId, name, this);
	this->name = name;
	this->comm = comm;
	this->cname = "Unset";
	roomId = -1;
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
	return fields.end() != fields.find(id);
}

Field* Device::getField(unsigned char id) {
	return fields[id];
}

void Device::setField(unsigned char id, Field* field) {
	if (hasField(id)) {
		delete fields[id];
	}
	fields[id] = field;
}

} /* namespace DVS */
