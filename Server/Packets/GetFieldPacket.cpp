/*
 * GetFieldPacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "GetFieldPacket.h"

namespace dvs {

GetFieldPacket::GetFieldPacket(Device *device, unsigned char id) :
		Packet(5, device->getId(), Get_Field) {
	data[4] = id;
}

} /* namespace dvs */
