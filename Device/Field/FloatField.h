/*
 * FloatField.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef FLOATFIELD_H_
#define FLOATFIELD_H_

#include "Field.h"

namespace dvs {

class FloatField: public dvs::Field {
public:
	FloatField(string name, unsigned char id, bool writable, bool vol);
	virtual ~FloatField();

	void setString(unsigned char* value);

	unsigned char* getString();

	unsigned int getLength();
private:
	float value;
	unsigned char l[5];
};

} /* namespace dvs */
#endif /* FLOATFIELD_H_ */
