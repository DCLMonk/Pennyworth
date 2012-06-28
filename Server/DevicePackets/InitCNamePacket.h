/*
 * InitCNamePacket.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef INITCNAMEPACKET_H_
#define INITCNAMEPACKET_H_

#include "Packet.h"

namespace dvs {

class InitCNamePacket: public dvs::Packet {
public:
	InitCNamePacket(unsigned char* data);
};

} /* namespace dvs */
#endif /* INITCNAMEPACKET_H_ */
