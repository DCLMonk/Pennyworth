/*
 * SetOnePacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "SetOnePacket.h"
#include "../Device/Field/Field.h"
#include "../Device/Field/FixedField.h"

namespace dvs {

SetOnePacket::SetOnePacket(unsigned char *data) :
		Packet(data) {
	unsigned char id = data[4];
	Device* device = getDevice();
	Field* field = device->getField(id);

	if (field->getType() == FIXED) {
		FixedField *ff = (FixedField*)field;
		ff->setOne((((unsigned int)data[6]) << 8) | data[5]);
	}
}

} /* namespace dvs */
