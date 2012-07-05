/*
 * Field.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Field.h"
#include <stdio.h>
#include "SetFieldPacket.h"

namespace dvs {

string typeStrings[] = { "Boolean", "Integer", "Floating Point", "Fixed Point",
		"String" };

Field::Field(FieldType type, string name, unsigned char id, bool writable,
		bool vol, Device* device) {
	this->name = name;
	this->id = id;
	this->writable = writable;
	this->vol = vol;
	this->device = device;
	this->type = type;
}

Field::~Field() {
}

void Field::setString(unsigned char* value) {
	printf("Warning: Unimplemented setString Field Used\n");
}

unsigned char* Field::getString() {
	printf("Warning: Unimplemented getString Field Used\n");
	return NULL;
}

unsigned int Field::getLength() {
	printf("Warning: Unimplemented getLength Field Used\n");
	return 0;
}

void Field::setRealString(string val) {
	printf("Warning: Unimplemented setRealString Field Used\n");
}

bool Field::isWritable() {
	return writable;
}

bool Field::isVolatile() {
	return vol;
}

string Field::getName() {
	return name;
}

FieldType Field::getType() {
	return type;
}

unsigned char Field::getId() {
	return id;
}

void Field::sendPacket() {
	SetFieldPacket packet(device, id);
	packet.send();
}

Device* Field::getDevice() {
	return device;
}

} /* namespace dvs */
