/*
 * InitFieldPacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "InitFieldPacket.h"

namespace dvs {

InitFieldPacket::InitFieldPacket(unsigned char* data) :
		Packet(data) {
	unsigned char type = data[4];
	bool writable = data[5];
	bool vol = data[6];
	unsigned char id = data[7];
	string name((const char *) (data + 8));
	Device* device = getDevice();

	switch (type) {
	case 0:
		device->setField(id, new BooleanField(name, id, writable, vol));
		break;
	case 1:
		device->setField(id, new IntegerField(name, id, writable, vol));
		break;
	case 2:
		device->setField(id, new FloatField(name, id, writable, vol));
		break;
	case 3:
		device->setField(id, new FixedField(name, id, writable, vol));
		break;
	case 4:
		device->setField(id, new StringField(name, id, writable, vol));
		break;
	default:
		printf("Invalid Field Type: %d\n", type);
		break;
	}
}

} /* namespace dvs */
