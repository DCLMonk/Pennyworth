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
 * DeviceDefPacket.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */

#include "DeviceDefPacket.h"
#include "stdlib.h"

namespace dvs {

DeviceDefPacket::DeviceDefPacket(string data, CCommunicator* comm) : CPacket(data, comm) {
//	this->device = device;
	int id = atoi((*this->args)[2].c_str());
	device = Device::getDevice(comm, id, (*this->args)[3].c_str());
	device->setCName((*this->args)[4]);
	int roomId = atoi((*this->args)[5].c_str());
	device->setRoom(roomId);
	int icon = atoi((*this->args)[6].c_str());
	int x = atoi((*this->args)[7].c_str());
	int y = atoi((*this->args)[8].c_str());
	device->setIcon(icon);
	device->setLoc(x, y);
}

DeviceDefPacket::~DeviceDefPacket() {

}

Device* DeviceDefPacket::getDevice() {
	return device;
}

} /* namespace dvs */
