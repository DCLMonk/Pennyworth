/*
 * SendFieldPacket.cpp
 *
 *  Created on: Jul 5, 2012
 *      Author: jmonk
 */

#include "SendFieldPacket.h"

namespace dvs {

SendFieldPacket::SendFieldPacket(Field* field, User* user) : CPacket(SEND_FIELD, user) {
	this->field = field;
}

SendFieldPacket::~SendFieldPacket() {

}

void SendFieldPacket::streamData(stringstream& data) {
	data << ':';
	data << field->getDevice()->getId();
	data << ':';
	data << field->getId();
	data << ':';
	switch (field->getType()) {
	case BOOL:
		if (((BooleanField*)field)->getBool()) {
			data << "True";
		} else {
			data << "False";
		}
		break;
	case INTEGER:
		data << ((IntegerField*)field)->getInt();
		break;
	case FLOAT:
		data << ((FloatField*)field)->getFloat();
		break;
	case FIXED:
		data << ((FixedField*)field)->getFloat();
		break;
	case STRING:
		data << ((StringField*)field)->getValue();
		break;
	}
}

} /* namespace dvs */
