/*
 * GetFieldsPacket.h
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */

#ifndef GETFIELDSPACKET_H_
#define GETFIELDSPACKET_H_

#include <CPacket.h>

namespace dvs {

class GetFieldsPacket: public dvs::CPacket {
public:
	GetFieldsPacket(string data);
	virtual ~GetFieldsPacket();
};

} /* namespace dvs */
#endif /* GETFIELDSPACKET_H_ */
