/*
 * SerialComm.h
 *
 *  Created on: Jun 20, 2012
 *      Author: jmonk
 */

#ifndef SERIALCOMM_H_
#define SERIALCOMM_H_

#include "Communicator.h"

namespace dvs {

class SerialComm: public Communicator {
public:
	SerialComm(char* device);
	virtual ~SerialComm();

	virtual void sendPacket(Packet* packet);
	virtual Packet* getPacket();
private:

	int fd;
	unsigned int size;
	unsigned int index;
};

} /* namespace dvs */
#endif /* SERIALCOMM_H_ */
