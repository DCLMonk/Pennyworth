/*
 * Field.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Field.h"
#include <stdio.h>

namespace dvs {

Field::Field(string name, unsigned char id, bool writable, bool vol) {
	this->name = name;
	this->id = id;
	this->writable = writable;
	this->vol = vol;
}

Field::~Field() {
}

void Field::setString(unsigned char* value) {
	printf("Warning: Unimplemented setString Field Used\n");
}

unsigned char* Field::getString() {
	printf("Warning: Unimplemented getString Field Used\n");
	return NULL;
}

unsigned int Field::getLength() {
	printf("Warning: Unimplemented getLength Field Used\n");
	return NULL;
}

} /* namespace dvs */
