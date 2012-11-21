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
 * SendFieldPacket.cpp
 *
 *  Created on: Jul 5, 2012
 *      Author: jmonk
 */

#include "SendFieldPacket.h"
#include "stdlib.h"

namespace dvs {

SendFieldPacket::SendFieldPacket(string data, CCommunicator* comm): CPacket(data, comm) {
	this->field = field;
	int id = atoi((*this->args)[2].c_str());
	Device* device = Device::getDevice(id);
	if (device != NULL) {
		int fid = atoi((*this->args)[3].c_str());
		Field* field = device->getField(fid);
		if (field != NULL) {
			field->setRealString((*this->args)[4]);
		}
	}
}

SendFieldPacket::~SendFieldPacket() {

}

} /* namespace dvs */
