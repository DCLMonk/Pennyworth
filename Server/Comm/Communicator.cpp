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
 * Communicator.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Communicator.h"

std::vector<dvs::Communicator*> comms;

namespace dvs {

Communicator::Communicator() {
	commId = comms.size();
	comms.push_back(this);
	index = 0;
	size = 0;
	name = "Unset Name";
}

Communicator::~Communicator() {
}

void Communicator::remove() {
	printf("remove: Removing %d\n", commId);
	comms.erase(comms.begin() + commId);
}

void Communicator::sendPacket(Packet* packet) {
	unsigned char* data = packet->getData();
	unsigned int length = packet->getLength();
	if (packet->getDevice() != NULL) {
		if (length > packet->getDevice()->getMaxLength()) {
			length = packet->getDevice()->getMaxLength();
			data[length - 1] = '\0';
		}
	}
	this->writeBytes(data, length);
}

void Communicator::getPacket() {
	if (index == 0) {
		int rd = this->readBytes(buffer, 1);
		if (rd > 0) {
			size = buffer[0];
			index = 1;
		}
	} else {
		int rd = this->readBytes(buffer + index, 1 + size - index);
		if (rd > 0) {
			index += rd;
			if (index == size + 1) {
				makePacket();
				for (unsigned int i = 0; i < index; i++) {
					buffer[i] = 0;
				}
				index = 0;
			}
		}
	}
}

void Communicator::writeBytes(unsigned char* data, unsigned int length) {
	printf("Warning: Unimplemented Communicator in Use\n");
}

int Communicator::readBytes(unsigned char* data, unsigned int length) {
	printf("Warning: Unimplemented Communicator in Use\n");
	return -1;
}

void Communicator::makePacket() {
	PacketType type = (PacketType) buffer[3];

	switch (type) {
	case Start:
		makeStart();
		break;
	case Init:
		makeInit();
		break;
	case Init_Common_Name:
		makeInitCName();
		break;
	case Init_Location:
		makeInitLoc();
		break;
	case Init_Field:
		makeInitField();
		break;
	case Get_Field:
		makeGetField();
		break;
	case Field_Value:
		makeFieldValue();
		break;
	case Set_Field:
		makeSetField();
		break;
	case Subscribe:
		makeSubscribe();
		break;
	case Set_One:
		makeSetOne();
		break;
	case Max_Length:
		makeMaxLength();
		break;
	}
}

void Communicator::makeStart() {
//	StartPacket start(buffer);
}

void Communicator::makeInit() {
	InitPacket init(buffer);
}

void Communicator::makeInitCName() {
	InitCNamePacket initCName(buffer);
}

void Communicator::makeInitLoc() {
	InitLocationPacket initLoc(buffer);
}

void Communicator::makeInitField() {
	InitFieldPacket initField(buffer);
}

void Communicator::makeGetField() {
//	GetFieldPacket getField(buffer);
}

void Communicator::makeFieldValue() {
	FieldValuePacket fieldValue(buffer);
}

void Communicator::makeSetField() {
//	SetFieldPacket setField(buffer);
}

void Communicator::makeSubscribe() {
//	SubscribePacket subscribe(buffer);
}

void Communicator::makeSetOne() {
	SetOnePacket setOne(buffer);
}

void Communicator::makeMaxLength() {
	MaxLengthPacket maxLength(buffer);
}

string Communicator::toString() {
	return name;
}

} /* namespace dvs */
