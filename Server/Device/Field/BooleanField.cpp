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
	// TODO Auto-generated constructor stub

}

BooleanField::~BooleanField() {
	// TODO Auto-generated destructor stub
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
	this->sendPacket();
}

} /* namespace dvs */
