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
 * InitLocationPacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "InitLocationPacket.h"

namespace dvs {

InitLocationPacket::InitLocationPacket(unsigned char* data) :
		Packet(data) {
	Device* device = getDevice();
	float x = ((((unsigned int) data[6]) << 8) | data[5]) / 65535.0f;
	float y = ((((unsigned int) data[8]) << 8) | data[7]) / 65535.0f;
	device->setRoom(data[4]);
	device->setLoc(x, y);

	device->setIcon(data[9]);
}

} /* namespace dvs */
