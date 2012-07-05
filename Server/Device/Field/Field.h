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

class Device;

typedef enum {
	BOOL=0,
	INTEGER=1,
	FLOAT=2,
	FIXED=3,
	STRING=4
} FieldType;

extern string typeStrings[];

class Field {
public:
	Field(FieldType type, string name, unsigned char id, bool writable, bool vol, Device* device);
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
	Device* getDevice();

protected:
	void sendPacket();
private:
	bool writable;
	bool vol;
	string name;
	FieldType type;
	unsigned char id;
	Device* device;
};

} /* namespace dvs */
#include "../Device.h"

#include "BooleanField.h"
#include "IntegerField.h"
#include "FloatField.h"
#include "FixedField.h"
#include "StringField.h"

#endif /* FIELD_H_ */
