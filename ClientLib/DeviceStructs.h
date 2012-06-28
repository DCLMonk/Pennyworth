/*
 * DeviceStructs.h
 *
 *  Created on: Jun 21, 2012
 *      Author: jmonk
 */

#ifndef DEVICESTRUCTS_H_
#define DEVICESTRUCTS_H_


typedef enum {
	BOOL=0,
	INT,
	FLOAT,
	FIXED,
	STRING
} FieldType;

typedef struct {
	FieldType type;
	unsigned char id;
	char *name;
	unsigned char vol;
	unsigned char writable;
	unsigned char changed;
	unsigned char subscribed;
	FieldList listener;
	void* field;
} FieldDef;

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 64
#endif

typedef struct {
	char buffer[BUFFER_LENGTH];
	unsigned int index;
	unsigned int length;
	unsigned int state;
	unsigned char initialized;
	SendRoutine send;
} CommManager;

typedef struct {
	CommManager comm;
	unsigned int deviceId;
	unsigned char roomId;
	char *name;
	char *cname;
	unsigned int x;
	unsigned int y;
	unsigned char icon;
	unsigned int nfields;
	FieldDef *fields;
} Device;

typedef struct {
	unsigned char value;
} BoolField;

typedef struct {
	unsigned int value;
} IntField;

typedef struct {
	unsigned int value;
	unsigned int one;
} FixedField;

typedef struct {
	char* value;
} StringField;

#endif /* DEVICESTRUCTS_H_ */
