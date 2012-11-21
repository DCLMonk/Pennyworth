/*
 * PacketListener.cpp
 *
 *  Created on: Nov 21, 2012
 *      Author: jmonk
 */

#include "PacketListener.h"

namespace dvs {

PacketListener::PacketListener(int packetType, void* data, Listener listener) {
	this->packetType = packetType;
	this->listener = listener;
	this->data = data;
}

PacketListener::~PacketListener() {

}

} /* namespace dvs */
