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
 * CCommandPacket.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: jmonk
 */

#include "CCommandPacket.h"
#include "CommandInterface.h"
#include <stdio.h>

void buf_putch(char c) {

}

namespace dvs {

CCommandPacket::CCommandPacket(std::string data) : CPacket(data) {
	if (this->args->size() >= 3) {
		buffer[0] = '\0';
		instance->commandHandle((char *)(*args)[2].c_str(), buffer, 2048);
		this->send();
	}
}

CCommandPacket::~CCommandPacket() {

}

void CCommandPacket::streamData(stringstream& data) {
	for (int i = 0; i < 2048; i++) {
		if (buffer[i] == ':') buffer[i] = ';';
		if (buffer[i] == '\n') buffer[i] = '\f';
	}

	string out(buffer);

	data << ':';
	data << out;
}

} /* namespace dvs */
