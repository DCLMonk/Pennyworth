/*
 * SetOnePacket.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef SETONEPACKET_H_
#define SETONEPACKET_H_

#include "Packet.h"

namespace dvs {

// WRITE Later
class SetOnePacket: public dvs::Packet {
public:
	SetOnePacket(unsigned char *data);
};

} /* namespace dvs */
#endif /* SETONEPACKET_H_ */
