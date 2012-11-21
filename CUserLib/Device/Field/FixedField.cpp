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
 * FixedField.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "FixedField.h"
#include <stdlib.h>

namespace dvs {

FixedField::FixedField(string name, unsigned char id, bool writable, bool vol, Device* device) :
		Field(FIXED, name, id, writable, vol, device) {
}

FixedField::~FixedField() {

}

void FixedField::setString(unsigned char* value) {
	this->value = value[1];
	this->value <<= 8;
	this->value |= value[0];
}

unsigned char* FixedField::getString() {
	array[0] = (char) (value & 0xff);
	array[1] = (char) ((value >> 8) & 0xff);
	array[2] = '\0';
	return array;
}

unsigned int FixedField::getLength() {
	return 3;
}

void FixedField::setRealString(string val) {
	this->value = (unsigned int)(this->o * atof(val.c_str()));
	this->sendPacket();
}

float FixedField::getFloat() {
	return ((float)this->value) / this->o;
}

void FixedField::setOne(unsigned int newOne) {
	this->o = newOne;
}

unsigned int FixedField::getOne() {
	return this->o;
}

} /* namespace dvs */
