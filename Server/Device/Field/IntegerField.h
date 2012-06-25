/*
 * IntegerField.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef INTEGERFIELD_H_
#define INTEGERFIELD_H_
#include "Field.h"

namespace dvs {

class IntegerField: public dvs::Field {
public:
	IntegerField(string name, unsigned char id, bool writable, bool vol, Device* device);
	virtual ~IntegerField();

	void setRealString(string val);

	void setString(unsigned char* value);

	unsigned char* getString();

	unsigned int getLength();

	int getInt();
private:
	int value;
	unsigned char l[5];
};

} /* namespace dvs */
#endif /* INTEGERFIELD_H_ */
