/*
 * FixedField.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef FIXEDFIELD_H_
#define FIXEDFIELD_H_

#include "Field.h"

namespace dvs {

class FixedField: public dvs::Field {
public:
	FixedField(string name, unsigned char id, bool writable, bool vol, Device* device);
	virtual ~FixedField();

	void setRealString(string val);

	void setString(unsigned char* value);

	unsigned char* getString();

	unsigned int getLength();

	float getFloat();
	void setOne(unsigned int one);
	unsigned int getOne();
private:
	unsigned int value;
	float fvalue;
	unsigned char array[3];
	unsigned int o;
};

} /* namespace dvs */
#endif /* FIXEDFIELD_H_ */
