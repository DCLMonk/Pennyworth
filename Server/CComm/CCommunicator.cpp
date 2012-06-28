/*
 * CCommunicator.cpp
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#include "CCommunicator.h"

namespace dvs {

CCommunicator::CCommunicator() {
	// TODO Auto-generated constructor stub

}

CCommunicator::~CCommunicator() {
	delete user;
}

void CCommunicator::send(CPacket* packet) {
	// Send packet
}

}
