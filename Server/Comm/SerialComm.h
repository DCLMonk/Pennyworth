/*
 * SerialComm.h
 *
 *  Created on: Jun 20, 2012
 *      Author: jmonk
 */

#ifndef SERIALCOMM_H_
#define SERIALCOMM_H_

#include "Communicator.h"
#include "SocketComm.h"

namespace dvs {

class SerialComm: public SocketComm {
public:
	SerialComm(char* device);
};

} /* namespace dvs */
#endif /* SERIALCOMM_H_ */
