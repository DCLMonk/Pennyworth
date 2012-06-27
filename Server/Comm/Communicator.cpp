/*
 * Communicator.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Communicator.h"

namespace dvs {

Communicator::Communicator() {

}

Communicator::~Communicator() {
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

} /* namespace dvs */
