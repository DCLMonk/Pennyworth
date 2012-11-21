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
 * BooleanField.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "BooleanField.h"
#include <stdlib.h>

namespace dvs {

BooleanField::BooleanField(string name, unsigned char id, bool writable,
		bool vol, Device* device) :
		Field(BOOL, name, id, writable, vol, device) {


}

BooleanField::~BooleanField() {

}

void BooleanField::setString(unsigned char* value) {
	this->value = value[0] > 0;
}

unsigned char* BooleanField::getString() {
	array[0] = value ? (char) 1 : (char) 0;
	array[1] = '\0';
	return array;
}

unsigned int BooleanField::getLength() {
	return 2;
}

void BooleanField::setBool(bool value) {
	this->value = value;
}
bool BooleanField::getBool() {
	return value;
}

void BooleanField::setRealString(string val) {
	if ((val.find('t') != string::npos) || (val.find('T') != string::npos)) {
		this->value = true;
	} else if ((val.find('f') != string::npos) || (val.find('F') != string::npos)) {
		this->value = false;
	} else {
		int v = atoi(val.c_str());
		this->value = v != 0;
	}
//	this->sendPacket();
}

} /* namespace dvs */
