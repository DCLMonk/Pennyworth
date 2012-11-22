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
 * FieldInfoPacket.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */

#include "FieldInfoPacket.h"
#include "Util.h"
#include <stdio.h>

namespace dvs {

FieldInfoPacket::FieldInfoPacket(string data, CCommunicator* comm) : CPacket(data, comm) {
	this->field = field;
	int id = atoi((*this->args)[2].c_str());
	Device* device = Device::getDevice(id);
	if (device != NULL) {
		int fid = atoi((*this->args)[3].c_str());
		field = device->getField(fid);
		FieldType type = (FieldType)(atoi((*this->args)[5].c_str()));
		string name = (*this->args)[4];
		bool writable = Util::toBool((*this->args)[6]);
		bool vol = Util::toBool((*this->args)[7]);
		if (field == NULL) {
			switch (type) {
			case BOOL:
				field = new BooleanField(name, fid, writable, vol, device);
				break;
			case INTEGER:
				field = new IntegerField(name, fid, writable, vol, device);
				break;
			case FLOAT:
				field = new FloatField(name, fid, writable, vol, device);
				break;
			case FIXED:
				field = new FixedField(name, fid, writable, vol, device);
				break;
			case STRING:
				field = new StringField(name, fid, writable, vol, device);
				break;
			}
			device->setField(id, field);
		}
	}
}

FieldInfoPacket::~FieldInfoPacket() {

}

Field* FieldInfoPacket::getField() {
	return field;
}

} /* namespace dvs */
