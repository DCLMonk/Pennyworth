/*
 * FieldInfoPacket.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */

#include "FieldInfoPacket.h"

namespace dvs {

FieldInfoPacket::FieldInfoPacket(Field* field, User* user) : CPacket(FIELD_INFO, user) {
	this->field = field;
}

FieldInfoPacket::~FieldInfoPacket() {

}

void FieldInfoPacket::streamData(stringstream& data) {
	data << ':';
	data << field->getId();

	data << ':';
	data << field->getName();

	data << ':';
	data << field->getType();

	data << ':';
	data << field->isWritable();

	data << ':';
	data << field->isVolatile();
}

} /* namespace dvs */
