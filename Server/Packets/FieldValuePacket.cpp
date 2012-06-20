/*
 * FieldValuePacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "FieldValuePacket.h"
#include "SetFieldPacket.h"

namespace dvs {

FieldValuePacket::FieldValuePacket(unsigned char *data) : Packet(data) {
	unsigned char id = data[4];
	Device* device = getDevice();
	Field* field = device->getField(id);

	field->setString(data + 5);
	SetFieldPacket packet(device, id);
	packet.send();
}

} /* namespace dvs */
