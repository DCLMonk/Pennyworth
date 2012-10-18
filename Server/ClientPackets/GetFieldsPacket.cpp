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
 * GetFieldsPacket.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */
#include <stdio.h>
#include <stdlib.h>
#include "GetFieldsPacket.h"
#include "FieldInfoPacket.h"

namespace dvs {

GetFieldsPacket::GetFieldsPacket(string data) : CPacket(data) {
	if (this->args->size() >= 3) {
		int id = atoi((*args)[2].c_str());
		Device* device = Device::getDevice(id);
		if (device != NULL) {
			if (args->size() >= 4) {
				int fid = atoi((*args)[3].c_str());
				if (device->hasField(fid)) {
					FieldInfoPacket packet(device->getField(fid), user);
					packet.send();
				} else {
					printf("Invalid Field Requested\n");
				}
			} else {
				for (unsigned int i = 0; i < device->getMaxField(); i++) {
					if (device->hasField(i)) {
						FieldInfoPacket packet(device->getField(i), user);
						packet.send();
					}
				}
			}
		} else {
			printf("Invalid Device Requested\n");
		}
	} else {
		printf("Warning: Invalid Get Fields Packet\n");
	}
}

GetFieldsPacket::~GetFieldsPacket() {

}

} /* namespace dvs */
