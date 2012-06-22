/*
 * SocketComm.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef SOCKETCOMM_H_
#define SOCKETCOMM_H_

#include "Communicator.h"
namespace dvs {

class SocketComm: public Communicator {
public:
	SocketComm(int fd);

	~SocketComm();

	virtual void sendPacket(Packet* packet);
	virtual Packet* getPacket();
private:
	int fd;
	unsigned int size;
	unsigned int index;
};

} /* namespace dvs */

#endif /* SOCKETCOMM_H_ */
