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

float FloatField::getFloat() {
	return this->value;
}

} /* namespace dvs */
