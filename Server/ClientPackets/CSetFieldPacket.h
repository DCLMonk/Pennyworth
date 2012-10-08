/*
 * CSetFieldPacket.h
 *
 *  Created on: Oct 7, 2012
 *      Author: jmonk
 */

#ifndef CSETFIELDPACKET_H_
#define CSETFIELDPACKET_H_

#include <CPacket.h>

namespace dvs {

class CSetFieldPacket: public dvs::CPacket {
public:
	CSetFieldPacket(string data);
	virtual ~CSetFieldPacket();
};

} /* namespace dvs */
#endif /* CSETFIELDPACKET_H_ */
