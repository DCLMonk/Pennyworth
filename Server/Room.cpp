/*
 * Room.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Room.h"

namespace dvs {

Room::Room(int id) {
	this->id = id;
}

Room::~Room() {
	// TODO Auto-generated destructor stub
}

void Room::addDevice(Device* device) {
	devices.insert(device);
}

void Room::remDevice(Device* device) {
	devices.erase(device);
}

int Room::getId() {
	return id;
}

} /* namespace dvs */
