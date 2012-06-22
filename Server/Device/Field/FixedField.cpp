/*
 * FixedField.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "FixedField.h"

namespace dvs {

FixedField::FixedField(string name, unsigned char id, bool writable, bool vol) :
		Field(name, id, writable, vol) {
	// TODO Auto-generated constructor stub

}

FixedField::~FixedField() {
	// TODO Auto-generated destructor stub
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

} /* namespace dvs */
