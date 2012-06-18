/*
 * StartPacket.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef STARTPACKET_H_
#define STARTPACKET_H_

#include "Packet.h"

namespace dvs {

class StartPacket: public dvs::Packet {
public:
	StartPacket() : Packet(3, 0, (unsigned char)Start) {

	}
};

} /* namespace dvs */
#endif /* STARTPACKET_H_ */
