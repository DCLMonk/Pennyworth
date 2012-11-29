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
 * PacketListener.cpp
 *
 *  Created on: Nov 21, 2012
 *      Author: jmonk
 */

#include "PacketListener.h"

namespace dvs {

PacketListener::PacketListener(int packetType, void* data, Listener listener) {
	this->packetType = packetType;
	this->listener = listener;
	this->data = data;
}

PacketListener::~PacketListener() {

}

} /* namespace dvs */
