/*
 * BooleanField.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "BooleanField.h"

namespace dvs {

BooleanField::BooleanField(string name, unsigned char id, bool writable, bool vol) : Field(name, id, writable, vol) {
	// TODO Auto-generated constructor stub

}

BooleanField::~BooleanField() {
	// TODO Auto-generated destructor stub
}

void BooleanField::setString(unsigned char* value) {
	this->value = value[0] > 0;
}

unsigned char* BooleanField::getString() {
	array[0] = value?(char)1:(char)0;
	array[1] = '\0';
	return array;
}

unsigned int BooleanField::getLength() {
	return 2;
}

} /* namespace dvs */
