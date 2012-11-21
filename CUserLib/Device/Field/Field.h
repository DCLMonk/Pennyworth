/**
 * Pennyworth - A new smarthome protocol.
 * Copyright (C) 2012  Dream-Crusher Labs LLC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
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

	virtual void increment();

	bool isWritable();
	bool isVolatile();
	string getName();
	FieldType getType();
	unsigned char getId();
	Device* getDevice();

	void sendToServer();

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
