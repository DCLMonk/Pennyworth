/*
 * LoginPacket.h
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#ifndef LOGINPACKET_H_
#define LOGINPACKET_H_

#include "CPacket.h"

namespace dvs {

class LoginPacket: public dvs::CPacket {
public:
	LoginPacket(string data);
	virtual ~LoginPacket();
};

} /* namespace dvs */
#endif /* LOGINPACKET_H_ */
