/*
 * Communicator.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Communicator.h"

namespace dvs {

Communicator::Communicator() {

}

Communicator::~Communicator() {
}

void Communicator::sendPacket(Packet* packet) {
	printf("Warning: Unimplemented Communicator in Use\n");
}

Packet* Communicator::getPacket() {
	printf("Warning: Unimplemented Communicator in Use\n");
}

} /* namespace dvs */
