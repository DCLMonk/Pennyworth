/*
 * InitLocationPacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "InitLocationPacket.h"

namespace dvs {

InitLocationPacket::InitLocationPacket(unsigned char* data) : Packet(data) {
	Device* device = getDevice();
	float x = ((((unsigned int)data[6]) << 8) | data[5]) / 65535.0f;
	float y = ((((unsigned int)data[8]) << 8) | data[7]) / 65535.0f;
	device->setRoom(data[4]);
	device->setLoc(x, y);

	device->setIcon(data[9]);
}

} /* namespace dvs */
