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
 * InitPacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "InitPacket.h"
#include <string.h>
#include <string>

using namespace std;

namespace dvs {

InitPacket::InitPacket(unsigned char *data) :
		Packet(data) {
	string name((const char *) (data + 4));
	InitPacket packet(Device::getDevice(Packet::getCurrentComm(), name));
	packet.getDevice()->setComm(Packet::getCurrentComm());
	packet.send();
}

InitPacket::InitPacket(Device *device) :
		Packet(device->getName().length() + 5, device->getId(), Init) {
	memcpy(data + 4, device->getName().c_str(), device->getName().length() + 1);
}

} /* namespace dvs */
