/*
 * InitCNamePacket.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "InitCNamePacket.h"
#include <string>
using namespace std;

namespace dvs {

InitCNamePacket::InitCNamePacket(unsigned char* data) : Packet(data) {
	string name((const char *)data + 4);

	getDevice()->setCName(name);
}

} /* namespace dvs */
