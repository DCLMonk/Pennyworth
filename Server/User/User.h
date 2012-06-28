/*
 * User.h
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#ifndef USER_H_
#define USER_H_

namespace dvs {

class CPacket;
class CCommunicator;

class User {
public:
	User(CCommunicator* comm);
	virtual ~User();

	void send(CPacket* packet);

	unsigned int getId();

	CCommunicator* getComm();
private:
	CCommunicator* comm;
	unsigned int id;
};

}

#endif /* USER_H_ */
