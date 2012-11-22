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
 * FloatField.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "FloatField.h"
#include <stdlib.h>

namespace dvs {

FloatField::FloatField(string name, unsigned char id, bool writable, bool vol, Device* device) :
		Field(FLOAT, name, id, writable, vol, device) {

}

FloatField::~FloatField() {

}

void FloatField::setString(unsigned char* value) {
	unsigned char *l = (unsigned char *) &value;
	l[0] = value[3];
	l[1] = value[2];
	l[2] = value[1];
	l[3] = value[0];
}

unsigned char* FloatField::getString() {
	unsigned char *value = (unsigned char *) &this->value;
	l[0] = value[3];
	l[1] = value[2];
	l[2] = value[1];
	l[3] = value[0];
	l[4] = '\0';
	;
	return l;
}

unsigned int FloatField::getLength() {
	return 5;
}

void FloatField::setRealString(string val) {
	this->value = (float)atof(val.c_str());
	this->sendPacket();
}

void FloatField::increment() {
	this->value++;
	sendToServer();
}

float FloatField::getFloat() {
	return this->value;
}

} /* namespace dvs */
