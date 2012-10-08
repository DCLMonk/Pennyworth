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
