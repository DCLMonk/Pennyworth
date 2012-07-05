/*
 * GetDevicesPacket.cpp
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */

#include "GetDevicesPacket.h"
#include "DeviceDefPacket.h"
#include <stdlib.h>

namespace dvs {

GetDevicesPacket::GetDevicesPacket(string data) : CPacket(data) {
	if (this->args->size() >= 3) {
		int id = atoi((*args)[2].c_str());
		if (Device::getDevice(id) != NULL) {
			DeviceDefPacket packet(Device::getDevice(id), user);

			packet.send();
		}
	} else {
		for (unsigned int i = 1; i < maxDeviceId; i++) {
			if (Device::getDevice(i) != NULL) {
				DeviceDefPacket packet(Device::getDevice(i), user);

				packet.send();
			}
		}
	}
}

GetDevicesPacket::~GetDevicesPacket() {

}

} /* namespace dvs */
