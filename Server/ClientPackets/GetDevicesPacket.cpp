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
 * GetDevicesPacket.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */

#include "GetDevicesPacket.h"
#include "DeviceDefPacket.h"
#include <stdlib.h>

namespace dvs {

GetDevicesPacket::GetDevicesPacket(string data) : CPacket(data) {
	if (this->args->size() >= 3) {
		int id = atoi((*args)[2].c_str());
		if (Device::getDevice(id) != NULL) {
			DeviceDefPacket packet(Device::getDevice(id), user);

			packet.send();
		}
	} else {
		for (unsigned int i = 1; i < maxDeviceId; i++) {
			if (Device::getDevice(i) != NULL) {
				DeviceDefPacket packet(Device::getDevice(i), user);

				packet.send();
			}
		}
	}
}

GetDevicesPacket::~GetDevicesPacket() {

}

} /* namespace dvs */
