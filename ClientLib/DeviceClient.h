/*
 * DeviceClient.h
 *
 *  Created on: Jun 19, 2012
 *      Author: jmonk
 */

#ifndef DEVICECLIENT_H_
#define DEVICECLIENT_H_


#ifdef __CDT_PARSER__
#define NULL (0)
#endif

typedef void(*FieldList)(void*);
typedef void(*SendRoutine)(char c);

#include "DeviceStructs.h"

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
void setFixedVal(unsigned int id, unsigned int value, Device* device);
void setStringVal(unsigned int id, char* value, Device* device);

void setOneVal(unsigned int id, unsigned int one, Device* device);

void setChangeListener(unsigned int id, FieldList listener, Device* device);

void recvChar(char c, Device* device);

#endif /* DEVICECLIENT_H_ */
