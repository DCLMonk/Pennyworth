/*
 * Communicator.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef COMMUNICATOR_H_
#define COMMUNICATOR_H_

#include "../Packets/Packet.h"

namespace dvs {

class Communicator {
public:
	Communicator();
	virtual ~Communicator();

	virtual void sendPacket(Packet* packet);
	virtual Packet* getPacket();
};

} /* namespace dvs */
#endif /* COMMUNICATOR_H_ */
