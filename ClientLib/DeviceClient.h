/*
 * DeviceClient.h
 *
 *  Created on: Jun 19, 2012
 *      Author: jmonk
 */

#ifndef DEVICECLIENT_H_
#define DEVICECLIENT_H_

typedef void(*FieldList)(void*);
typedef void(*SendRoutine)(char c);

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
#define BUFFER_LENGTH 256
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

Device* createDevice(char* uname, int maxFields, SendRoutine send);

void sendInitPacket(Device* device);

void setDeviceCName(char* name, Device* device);

void setDeviceLocation(unsigned char room, unsigned int x, unsigned int y,
								unsigned char icon, Device* device);

int addField(FieldType type, char* name, unsigned int id,
		unsigned char writable, unsigned char vol, Device* device);

unsigned char hasChanged(unsigned int id, Device* device);

unsigned char getBoolVal(unsigned int id, Device* device);
unsigned int getIntVal(unsigned int id, Device* device);
unsigned int getFixedVal(unsigned int id, Device* device);
char* getStringVal(unsigned int id, Device* device);

void setBoolVal(unsigned int id, unsigned char value, Device* device);
void setIntVal(unsigned int id, unsigned int value, Device* device);
void setFixedVal(unsigned int id, unsigned int value, unsigned int one, Device* device);
void setStringVal(unsigned int id, char* value, Device* device);

void setOneVal(unsigned int id, unsigned int one, Device* device);

void setChangeListener(unsigned int id, FieldList listener, Device* device);

void recvChar(char c, Device* device);

#endif /* DEVICECLIENT_H_ */
