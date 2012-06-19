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

class SocketComm : public Communicator {
public:
	SocketComm(int fd);

	~SocketComm();

	virtual void sendPacket(Packet* packet);
	virtual Packet* getPacket();

	void makePacket();
private:
	void makeStart();
	void makeInit();
	void makeInitCName();
	void makeInitLoc();
	void makeInitField();
	void makeGetField();
	void makeFieldValue();
	void makeSetField();
	void makeSubscribe();
	void makeSetOne();

	int fd;
	unsigned int size;
	unsigned int index;
	unsigned char buffer[256];
};

} /* namespace dvs */

#endif /* SOCKETCOMM_H_ */
