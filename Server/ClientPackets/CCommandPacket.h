/*
 * CCommandPacket.h
 *
 *  Created on: Aug 21, 2012
 *      Author: jmonk
 */

#ifndef CCOMMANDPACKET_H_
#define CCOMMANDPACKET_H_

#include "CPacket.h"
#include <string>

namespace dvs {

class CCommandPacket : public CPacket {
public:
	CCommandPacket(std::string data);
	virtual ~CCommandPacket();

	void streamData(stringstream& data);

private:
	char buffer[2048];
};

} /* namespace dvs */
#endif /* CCOMMANDPACKET_H_ */
