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
 * StringField.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "StringField.h"

namespace dvs {

StringField::StringField(string name, unsigned char id, bool writable, bool vol, Device* device) :
		Field(STRING, name, id, writable, vol, device) {

}

StringField::~StringField() {

}

void StringField::setString(unsigned char* value) {
	string n((const char *) value);
	this->value = n;
}

unsigned char* StringField::getString() {
	return (unsigned char *) value.c_str();
}

unsigned int StringField::getLength() {
	return value.length() + 1;
}

void StringField::setRealString(string val) {
	this->value = val;
	this->sendPacket();
}

string StringField::getValue() {
	return this->value;
}

} /* namespace dvs */
