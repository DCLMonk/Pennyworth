/*
 * BooleanField.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef BOOLEANFIELD_H_
#define BOOLEANFIELD_H_
#include "Field.h"

namespace dvs {

class BooleanField : public dvs::Field {
public:
	BooleanField(string name, unsigned char id, bool writable, bool vol);
	virtual ~BooleanField();

	void setString(unsigned char* value);

	unsigned char* getString();

	unsigned int getLength();

	void setBool(bool value);
	bool getBool();
private:
	bool value;
	unsigned char array[2];
};

} /* namespace dvs */
#endif /* BOOLEANFIELD_H_ */
