/*
 * FieldInfoPacket.h
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */

#ifndef FIELDINFOPACKET_H_
#define FIELDINFOPACKET_H_

#include "CPacket.h"

#include "Field.h"
#include "User.h"

namespace dvs {

class FieldInfoPacket : public CPacket{
public:
	FieldInfoPacket(Field* field, User* user);
	virtual ~FieldInfoPacket();

	void streamData(stringstream& data);

private:
	Field* field;
};

} /* namespace dvs */
#endif /* FIELDINFOPACKET_H_ */
