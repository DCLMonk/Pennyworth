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
	FixedField(string name, unsigned char id, bool writable, bool vol);
	virtual ~FixedField();

	void setString(unsigned char* value);

	unsigned char* getString();

	unsigned int getLength();
private:
	unsigned int value;
	unsigned int one;
	float fvalue;
	unsigned char array[3];
};

} /* namespace dvs */
#endif /* FIXEDFIELD_H_ */
