/*
 * GetFieldPacket.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef GETFIELDPACKET_H_
#define GETFIELDPACKET_H_

#include "Packet.h"

namespace dvs {

class GetFieldPacket : public dvs::Packet {
public:
	GetFieldPacket(Device *device, unsigned char id);
};

} /* namespace dvs */
#endif /* GETFIELDPACKET_H_ */
