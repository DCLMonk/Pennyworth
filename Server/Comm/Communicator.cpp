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
	printf("Warning: Unimplemented Communicator in Use\n");
}

Packet* Communicator::getPacket() {
	printf("Warning: Unimplemented Communicator in Use\n");
	return NULL;
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

} /* namespace dvs */
