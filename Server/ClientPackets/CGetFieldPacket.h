/*
 * CGetFieldPacket.h
 *
 *  Created on: Jul 5, 2012
 *      Author: jmonk
 */

#ifndef CGETFIELDPACKET_H_
#define CGETFIELDPACKET_H_

#include "CPacket.h"

namespace dvs {

class CGetFieldPacket: public dvs::CPacket {
public:
	CGetFieldPacket(string data);
	virtual ~CGetFieldPacket();
};

} /* namespace dvs */
#endif /* CGETFIELDPACKET_H_ */
