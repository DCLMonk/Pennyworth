/*
 * StringField.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef STRINGFIELD_H_
#define STRINGFIELD_H_

#include "Field.h"

namespace dvs {

class StringField: public dvs::Field {
public:
	StringField(string name, unsigned char id, bool writable, bool vol, Device* device);
	virtual ~StringField();

	void setRealString(string val);

	void setString(unsigned char* value);

	unsigned char* getString();

	unsigned int getLength();

	string getValue();
private:
	string value;
};

} /* namespace dvs */
#endif /* STRINGFIELD_H_ */
