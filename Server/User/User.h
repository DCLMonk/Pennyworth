/*
 * User.h
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#ifndef USER_H_
#define USER_H_

#include "CCommunicator.h"

namespace dvs {

class CPacket;

class User {
public:
	User(unsigned int id, CCommunicator* comm);
	virtual ~User();

	void send(CPacket* packet);

	unsigned int getId();
private:
	CCommunicator* comm;
	unsigned int id;
};

}

#endif /* USER_H_ */
