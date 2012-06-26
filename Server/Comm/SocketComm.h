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
	SocketComm();

	~SocketComm();

	void writeBytes(unsigned char* data, unsigned int length);

	int readBytes(unsigned char* data, unsigned int length);
protected:
	int fd;
};

} /* namespace dvs */

#endif /* SOCKETCOMM_H_ */
