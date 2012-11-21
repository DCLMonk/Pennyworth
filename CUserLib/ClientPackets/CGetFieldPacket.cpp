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
 * CGetFieldPacket.cpp
 *
 *  Created on: Jul 5, 2012
 *      Author: jmonk
 */

#include "CGetFieldPacket.h"
#include <stdio.h>
#include <stdlib.h>
#include "Field.h"

namespace dvs {

CGetFieldPacket::CGetFieldPacket(Field* field, Device* device, CCommunicator* comm) : CPacket(GET_FIELD, comm) {
//	if (this->args->size() >= 4) {
//		int id = atoi((*args)[2].c_str());
//		Device* device = Device::getDevice(id);
//		if (device != NULL) {
//			id = atoi((*args)[3].c_str());
//			Field* field = device->getField(id);
//			if (field != NULL) {
//				SendFieldPacket packet(field, user);
//				packet.send();
//			} else {
//				printf("Error: Invalid Field\n");
//			}
//		} else {
//			printf("Error: Invalid Device\n");
//		}
//	} else {
//		printf("Invalid GetField Packet\n");
//	}
	this->field = field;
	this->device = device;
}

CGetFieldPacket::~CGetFieldPacket() {

}

void CGetFieldPacket::streamData(stringstream& data) {
	data << device->getId();
	data << ":";
	data << field->getId();
}

} /* namespace dvs */
