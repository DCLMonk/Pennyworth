/*
 * MaxLengthPacket.h
 *
 *  Created on: Jun 26, 2012
 *      Author: jmonk
 */

#ifndef MAXLENGTHPACKET_H_
#define MAXLENGTHPACKET_H_

#include "Packet.h"

namespace dvs {

class MaxLengthPacket: public dvs::Packet {
public:
	MaxLengthPacket(unsigned char* data);
	virtual ~MaxLengthPacket();
};

} /* namespace dvs */
#endif /* MAXLENGTHPACKET_H_ */
