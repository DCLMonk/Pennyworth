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
 * UIDPacket.cpp
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#include "UIDPacket.h"
#include <stdio.h>
#include <stdlib.h>

namespace dvs {

UIDPacket::UIDPacket(string data, CCommunicator* comm) : CPacket(data, comm) {
	int id = atoi((*this->args)[1].c_str());
	comm->setId(id);
}

UIDPacket::~UIDPacket() {

}

void UIDPacket::streamData(stringstream& data) {

}

} /* namespace dvs */
