/*
 * SetFieldPacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "SetFieldPacket.h"
#include <string.h>

namespace dvs {

SetFieldPacket::SetFieldPacket(Device *device, unsigned char id) :
		Packet(device->getField(id)->getLength() + 5, device->getId(),
				Set_Field) {
	data[4] = id;
	memcpy(data + 5, device->getField(id)->getString(),
			device->getField(id)->getLength());
}

} /* namespace dvs */
