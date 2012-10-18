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
 * SetFieldPacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "SetFieldPacket.h"
#include <string.h>

namespace dvs {

SetFieldPacket::SetFieldPacket(Device *device, unsigned char id) :
		Packet(device->getField(id)->getLength() + 5, device->getId(),
				Set_Field) {
	data[4] = id;
	memcpy(data + 5, device->getField(id)->getString(),
			device->getField(id)->getLength());
}

} /* namespace dvs */
