/*
 * InitFieldPacket.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef INITFIELDPACKET_H_
#define INITFIELDPACKET_H_

#include "Packet.h"

namespace dvs {

class InitFieldPacket: public dvs::Packet {
public:
	InitFieldPacket(unsigned char* data);
};

} /* namespace dvs */
#endif /* INITFIELDPACKET_H_ */
