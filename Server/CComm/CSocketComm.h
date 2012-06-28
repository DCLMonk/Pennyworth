/*
 * SocketComm.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef CSOCKETCOMM_H_
#define CSOCKETCOMM_H_

#include "CCommunicator.h"
namespace dvs {

class CSocketComm: public CCommunicator {
public:
	CSocketComm(int fd);
	CSocketComm();

	~CSocketComm();

	void writeBytes(unsigned char* data, unsigned int length);

	int readBytes(unsigned char* data, unsigned int length);
protected:
	int fd;
};

} /* namespace dvs */

#endif /* CSOCKETCOMM_H_ */
