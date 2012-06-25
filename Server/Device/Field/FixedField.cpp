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
