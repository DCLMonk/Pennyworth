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

typedef enum {
	BOOL=0,
	INTEGER,
	FLOAT,
	FIXED,
	STRING
} FieldType;

extern string typeStrings[];

class Field {
public:
	Field(FieldType type, string name, unsigned char id, bool writable, bool vol);
	virtual ~Field();

	virtual void setRealString(string val);

	virtual void setString(unsigned char* value);

	virtual unsigned char* getString();

	virtual unsigned int getLength();

	bool isWritable();
	bool isVolatile();
	string getName();
	FieldType getType();
	unsigned char getId();

private:
	bool writable;
	bool vol;
	string name;
	FieldType type;
	unsigned char id;
};

} /* namespace dvs */

#include "BooleanField.h"
#include "IntegerField.h"
#include "FloatField.h"
#include "FixedField.h"
#include "StringField.h"

#endif /* FIELD_H_ */
