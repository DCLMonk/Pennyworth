/*
 * GetFieldsPacket.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */
#include <stdio.h>
#include "GetFieldsPacket.h"
#include "FieldInfoPacket.h"

namespace dvs {

GetFieldsPacket::GetFieldsPacket(string data) : CPacket(data) {
	if (this->args->size() >= 3) {
		int id = atoi((*args)[2].c_str());
		Device* device = Device::getDevice(id);
		if (device != null) {
			if (args->size() >= 4) {
				int fid = atoi((*args)[3].c_str());
				if (device->hasField(fid)) {
					FieldInfoPacket packet(device->getField(fid), user);
					packet.send();
				} else {
					printf("Invalid Field Requested\n");
				}
			} else {
				for (unsigned int i = 0; i < device->getMaxField(); i++) {
					if (device->hasField(i)) {
						FieldInfoPacket packet(device->getField(i), user);
						packet.send();
					}
				}
			}
		} else {
			printf("Invalid Device Requested\n");
		}
	} else {
		printf("Warning: Invalid Get Fields Packet\n");
	}
}

GetFieldsPacket::~GetFieldsPacket() {

}

} /* namespace dvs */
