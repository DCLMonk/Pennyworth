/*
 * SocketComm.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */
#include "SocketComm.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

namespace dvs {

SocketComm::SocketComm(int fd) {
	this->fd = fd;
	fcntl(fd, F_SETFL, O_NONBLOCK);
	StartPacket p;
	sendPacket(&p);
}

SocketComm::~SocketComm() {
	close(fd);
}

void SocketComm::sendPacket(Packet* packet) {
	write(fd, packet->getData(), packet->getLength());
}

Packet* SocketComm::getPacket() {
	if (index == 0) {
		int rd = read(fd, buffer, 1);
		if (rd > 0) {
			printf("Start: %d\n", buffer[0]);
			size = buffer[0];
			index = 1;
		}
	} else {
		int rd = read(fd, buffer + index, 1 + size - index);
		if (rd > 0) {
			printf("Read: %d\n", rd);
			index += rd;
			if (index == size + 1) {
				makePacket();
				index = 0;
			}
		}
	}
	return NULL;
}

void SocketComm::makePacket() {
	PacketType type = (PacketType)buffer[3];

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

void SocketComm::makeStart() {
//	StartPacket start(buffer);
}

void SocketComm::makeInit() {
	InitPacket init(buffer);
}

void SocketComm::makeInitCName() {
	InitCNamePacket initCName(buffer);
}

void SocketComm::makeInitLoc() {
	InitLocationPacket initLoc(buffer);
}

void SocketComm::makeInitField() {
	InitFieldPacket initField(buffer);
}

void SocketComm::makeGetField() {
//	GetFieldPacket getField(buffer);
}

void SocketComm::makeFieldValue() {
	FieldValuePacket fieldValue(buffer);
}

void SocketComm::makeSetField() {
//	SetFieldPacket setField(buffer);
}

void SocketComm::makeSubscribe() {
//	SubscribePacket subscribe(buffer);
}

void SocketComm::makeSetOne() {
//	SetOnePacket setOne(buffer);
}

} /* namespace dvs */
