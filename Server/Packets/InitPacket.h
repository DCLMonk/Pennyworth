/*
 * InitPacket.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef INITPACKET_H_
#define INITPACKET_H_

#include "Packet.h"

namespace dvs {

class InitPacket: public dvs::Packet {
public:
	InitPacket(unsigned char *data);
	InitPacket(Device *device);
};

} /* namespace dvs */
#endif /* INITPACKET_H_ */
