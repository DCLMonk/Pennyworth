/*
 * InitLocationPacket.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef INITLOCATIONPACKET_H_
#define INITLOCATIONPACKET_H_

#include "Packet.h"

namespace dvs {

class InitLocationPacket: public dvs::Packet {
public:
	InitLocationPacket(unsigned char* data);
};

} /* namespace dvs */
#endif /* INITLOCATIONPACKET_H_ */
