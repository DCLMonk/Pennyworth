/*
 * UIDPacket.h
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#ifndef UIDPACKET_H_
#define UIDPACKET_H_

#include "CPacket.h"

namespace dvs {

class UIDPacket: public dvs::CPacket {
public:
	UIDPacket(User* user);
	virtual ~UIDPacket();

	void streamData(stringstream& data);
};

} /* namespace dvs */
#endif /* UIDPACKET_H_ */
