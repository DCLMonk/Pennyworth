/*
 * DeviceDefPacket.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */

#include "DeviceDefPacket.h"

namespace dvs {

DeviceDefPacket::DeviceDefPacket(Device* device, User* user) : CPacket(DEVICE_DEF, user) {
	this->device = device;
}

DeviceDefPacket::~DeviceDefPacket() {

}

void DeviceDefPacket::streamData(stringstream& data) {
	data << ':';
	data << device->getId();

	data << ':';
	data << device->getName();

	data << ':';
	data << device->getCName();

	data << ':';
	data << device->getRoom();

	data << ':';
	data << device->getIcon();

	data << ':';
	data << device->getX();

	data << ':';
	data << device->getY();
}

} /* namespace dvs */
