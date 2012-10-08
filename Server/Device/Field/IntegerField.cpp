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
