/*
 * FieldValuePacket.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef FIELDVALUEPACKET_H_
#define FIELDVALUEPACKET_H_

#include "Packet.h"

namespace dvs {

class FieldValuePacket: public dvs::Packet {
public:
	FieldValuePacket(unsigned char *data);
};

} /* namespace dvs */
#endif /* FIELDVALUEPACKET_H_ */
