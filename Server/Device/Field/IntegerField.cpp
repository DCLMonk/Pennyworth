/*
 * IntegerField.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "IntegerField.h"

namespace dvs {

IntegerField::IntegerField(string name, unsigned char id, bool writable,
		bool vol) :
		Field(name, id, writable, vol) {
	// TODO Auto-generated constructor stub

}

IntegerField::~IntegerField() {
	// TODO Auto-generated destructor stub
}

void IntegerField::setString(unsigned char* value) {
	unsigned char *l = (unsigned char *) &value;
	l[0] = value[3];
	l[1] = value[2];
	l[2] = value[1];
	l[3] = value[0];
}

unsigned char* IntegerField::getString() {
	unsigned char *value = (unsigned char *) &this->value;
	l[0] = value[3];
	l[1] = value[2];
	l[2] = value[1];
	l[3] = value[0];
	l[4] = '\0';
	return l;
}

unsigned int IntegerField::getLength() {
	return 5;
}

} /* namespace dvs */
