/*
 * StringField.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "StringField.h"

namespace dvs {

StringField::StringField(string name, unsigned char id, bool writable, bool vol) : Field(name, id, writable, vol) {
	// TODO Auto-generated constructor stub

}

StringField::~StringField() {
	// TODO Auto-generated destructor stub
}

void StringField::setString(unsigned char* value) {
	string n((const char *)value);
	this->value = n;
}

unsigned char* StringField::getString() {
	return (unsigned char *)value.c_str();
}

unsigned int StringField::getLength() {
	return value.length();
}

} /* namespace dvs */
