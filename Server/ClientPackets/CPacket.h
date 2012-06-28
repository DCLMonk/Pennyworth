/*
 * CPacket.h
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#ifndef CPACKET_H_
#define CPACKET_H_

#include <string>
#include <sstream>
#include <vector>
#include "User.h"

using namespace std;

namespace dvs {

class CPacket {
public:
	CPacket(string data);
	CPacket(unsigned int id, User* user);
	virtual ~CPacket();

	string toString();
	virtual void streamData(stringstream& data);

	void send();

protected:
	User* user;
	unsigned int id;
	vector<string>* args;
};

typedef enum {
	LOGIN=1,
	UID=2,
	LOGIN_FAILED=3
} CPacketTypes;

}

#endif /* CPACKET_H_ */
