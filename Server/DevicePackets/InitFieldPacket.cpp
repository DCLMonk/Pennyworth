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
 * InitFieldPacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "InitFieldPacket.h"

namespace dvs {

InitFieldPacket::InitFieldPacket(unsigned char* data) :
		Packet(data) {
	unsigned char type = data[4];
	bool writable = data[5];
	bool vol = data[6];
	unsigned char id = data[7];
	string name((const char *) (data + 8));
	Device* device = getDevice();

	switch (type) {
	case 0:
		device->setField(id, new BooleanField(name, id, writable, vol, device));
		break;
	case 1:
		device->setField(id, new IntegerField(name, id, writable, vol, device));
		break;
	case 2:
		device->setField(id, new FloatField(name, id, writable, vol, device));
		break;
	case 3:
		device->setField(id, new FixedField(name, id, writable, vol, device));
		break;
	case 4:
		device->setField(id, new StringField(name, id, writable, vol, device));
		break;
	default:
		printf("Invalid Field Type: %d\n", type);
		break;
	}
}

} /* namespace dvs */
