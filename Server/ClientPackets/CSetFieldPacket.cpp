/*
 * CSetFieldPacket.cpp
 *
 *  Created on: Oct 7, 2012
 *      Author: jmonk
 */

#include "CSetFieldPacket.h"
#include <stdlib.h>

namespace dvs {

CSetFieldPacket::CSetFieldPacket(string data) : CPacket(data) {
	if (this->args->size() >= 5) {
		int id = atoi((*args)[2].c_str());
		Device* device = Device::getDevice(id);
		if (device != NULL) {
			int fid = atoi((*args)[3].c_str());
			if (device->hasField(fid)) {
				device->getField(fid)->setRealString((*args)[4]);
			} else {
				printf("Invalid Field Requested\n");
			}
		} else {
			printf("Invalid Device Requested\n");
		}
	} else {
		printf("Warning: Invalid Get Fields Packet\n");
	}
}

CSetFieldPacket::~CSetFieldPacket() {
}

} /* namespace dvs */
