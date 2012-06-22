/*
 * Field.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef FIELD_H_
#define FIELD_H_
#include <string>
using namespace std;

namespace dvs {

class Field {
public:
	Field(string name, unsigned char id, bool writable, bool vol);
	virtual ~Field();

	virtual void setString(unsigned char* value);

	virtual unsigned char* getString();

	virtual unsigned int getLength();
private:
	bool writable;
	bool vol;
	string name;
	unsigned char id;
};

} /* namespace dvs */

#include "BooleanField.h"
#include "IntegerField.h"
#include "FloatField.h"
#include "FixedField.h"
#include "StringField.h"

#endif /* FIELD_H_ */
