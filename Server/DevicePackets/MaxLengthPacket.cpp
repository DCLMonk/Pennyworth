/*
 * MaxLengthPacket.cpp
 *
 *  Created on: Jun 26, 2012
 *      Author: jmonk
 */

#include "MaxLengthPacket.h"

namespace dvs {

MaxLengthPacket::MaxLengthPacket(unsigned char* data) :
				Packet(data) {
	Device* device = getDevice();

	if (device != NULL) {
		device->setMaxLength(data[4]);
	}
}

MaxLengthPacket::~MaxLengthPacket() {

}

} /* namespace dvs */
