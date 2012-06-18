/*
 * Room.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Room.h"

namespace dvs {

Room::Room() {
	// TODO Auto-generated constructor stub

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

} /* namespace dvs */
