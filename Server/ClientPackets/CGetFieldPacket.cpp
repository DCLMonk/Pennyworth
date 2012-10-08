/*
 * CGetFieldPacket.cpp
 *
 *  Created on: Jul 5, 2012
 *      Author: jmonk
 */

#include "CGetFieldPacket.h"
#include <stdio.h>
#include <stdlib.h>

namespace dvs {

CGetFieldPacket::CGetFieldPacket(string data) : CPacket(data) {
	if (this->args->size() >= 4) {
		int id = atoi((*args)[2].c_str());
		Device* device = Device::getDevice(id);
		if (device != NULL) {
			id = atoi((*args)[3].c_str());
			Field* field = device->getField(id);
			if (field != NULL) {
				SendFieldPacket packet(field, user);
				packet.send();
			} else {
				printf("Error: Invalid Field\n");
			}
		} else {
			printf("Error: Invalid Device\n");
		}
	} else {
		printf("Invalid GetField Packet\n");
	}
}

CGetFieldPacket::~CGetFieldPacket() {
	// TODO Auto-generated destructor stub
}

} /* namespace dvs */
