/*
 * SetFieldPacket.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef SETFIELDPACKET_H_
#define SETFIELDPACKET_H_

#include "Packet.h"

namespace dvs {

class SetFieldPacket: public dvs::Packet {
public:
	SetFieldPacket(Device *device, unsigned char id);
};

} /* namespace dvs */
#endif /* SETFIELDPACKET_H_ */
