/*
 * LoginFailurePacket.h
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#ifndef LOGINFAILUREPACKET_H_
#define LOGINFAILUREPACKET_H_

#include "CPacket.h"

namespace dvs {

class LoginFailurePacket: public dvs::CPacket {
public:
	LoginFailurePacket(string error);
	virtual ~LoginFailurePacket();

	void streamData(stringstream& data);
private:
	string error;
};

} /* namespace dvs */
#endif /* LOGINFAILUREPACKET_H_ */
