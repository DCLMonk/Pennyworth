/*
 * CCommunicator.h
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#ifndef CCOMMUNICATOR_H_
#define CCOMMUNICATOR_H_

namespace dvs {

class CPacket;
class User;

class CCommunicator {
public:
	CCommunicator();
	virtual ~CCommunicator();

	void send(CPacket* packet);

	User* user;
};

}

#endif /* CCOMMUNICATOR_H_ */
