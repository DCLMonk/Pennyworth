/*
 * InitPacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "InitPacket.h"
#include <string.h>
#include <string>

using namespace std;

namespace dvs {

InitPacket::InitPacket(unsigned char *data) : Packet(data) {
	string name((const char *)(data + 4));
	InitPacket packet(Device::getDevice(Packet::getCurrentComm(), name));
	packet.getDevice()->setComm(Packet::getCurrentComm());
	packet.send();
	printf("Init Device: %d\n", packet.getDevice()->getId());
}

InitPacket::InitPacket(Device *device) : Packet(device->getName().length() + 5, device->getId(), Init) {
	memcpy(data + 4, device->getName().c_str(), device->getName().length() + 1);
}

} /* namespace dvs */
