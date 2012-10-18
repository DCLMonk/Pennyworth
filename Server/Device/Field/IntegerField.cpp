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
 * IntegerField.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "IntegerField.h"
#include <stdlib.h>

namespace dvs {

IntegerField::IntegerField(string name, unsigned char id, bool writable,
		bool vol, Device* device) :
		Field(INTEGER, name, id, writable, vol, device) {

}

IntegerField::~IntegerField() {

}

void IntegerField::setString(unsigned char* value) {
	unsigned char *l = (unsigned char *) &this->value;
	l[0] = value[3];
	l[1] = value[2];
	l[2] = value[1];
	l[3] = value[0];
}

unsigned char* IntegerField::getString() {
//	unsigned char *value = (unsigned char *) &this->value;
	for (unsigned int i = 0; i < 4; i++) {
		l[i] = (this->value >> (i * 8)) & 0xff;
	}
//	l[0] = value[3];
//	l[1] = value[2];
//	l[2] = value[1];
//	l[3] = value[0];
	l[4] = '\0';
	return l;
}

unsigned int IntegerField::getLength() {
	return 5;
}

void IntegerField::setRealString(string val) {
	this->value = atoi(val.c_str());
	this->sendPacket();
}

int IntegerField::getInt() {
	return this->value;
}

} /* namespace dvs */
