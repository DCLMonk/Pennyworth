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
 * Field.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Field.h"
#include <stdio.h>

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

void Field::increment() {
	printf("Warning: Unimplemented increment Field Used\n");
}

void Field::sendToServer() {
	CSetFieldPacket p(getDevice(), this, getDevice()->getComm());
	p.send();
}

void Field::sendPacket() {
	CSetFieldPacket packet(device, this, device->getComm());
	packet.send();
}

Device* Field::getDevice() {
	return device;
}

} /* namespace dvs */
