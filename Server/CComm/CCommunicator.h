/*
 * CCommunicator.h
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#ifndef CCOMMUNICATOR_H_
#define CCOMMUNICATOR_H_

#include <string>
#include "Runnable.h"
#include "CPacket.h"

namespace dvs {

#define BUF_LENGTH 256

class User;

class CCommunicator {
public:
	CCommunicator();
	virtual ~CCommunicator();

	void sendPacket(CPacket* packet);
	void getPacket();

	void makePacket(std::string packet);

	virtual void writeBytes(const char* data, unsigned int length);

	virtual int readBytes(char* data, unsigned int length);

	User* user;
protected:
	char buffer[BUF_LENGTH];
	char pbuffer[BUF_LENGTH];
	unsigned int index;
};

class CCommHandler: public Runnable {
public:
	CCommHandler(CCommunicator* comm) {
		this->comm = comm;
	}

	~CCommHandler() {
		delete comm;
	}

	void run() {
		CPacket::setCurrentComm(comm);
		(comm)->getPacket();
	}
private:
	CCommunicator* comm;
};

}

#endif /* CCOMMUNICATOR_H_ */
