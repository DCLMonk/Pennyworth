/*
 * SendFieldPacket.h
 *
 *  Created on: Jul 5, 2012
 *      Author: jmonk
 */

#ifndef SENDFIELDPACKET_H_
#define SENDFIELDPACKET_H_

#include "CPacket.h"

namespace dvs {

class SendFieldPacket: public dvs::CPacket {
public:
	SendFieldPacket(Field* field, User* user);
	virtual ~SendFieldPacket();

	void streamData(stringstream& data);

private:
	Field* field;
};

} /* namespace dvs */
#endif /* SENDFIELDPACKET_H_ */
