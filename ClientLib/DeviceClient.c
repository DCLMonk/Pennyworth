/*
 * DeviceClient.c
 *
 *  Created on: Jun 19, 2012
 *      Author: jmonk
 */

#include "DeviceClient.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#define NULL (0)

void sendLoc(Device* device);
void sendCName(Device* device);
void sendField(Device* device, FieldDef* field);
void sendValue(unsigned char id, Device* device);
void sendInitPackets(Device* device);
#define printf(x,...)

Device* createDevice(char* uname, int maxFields, SendRoutine send) {
	Device* device = (Device*)malloc(sizeof(Device));
	CommManager* comm = &device->comm;
	int i;

	device->fields = malloc(maxFields * sizeof(FieldDef));
	device->nfields = maxFields;
	for (i = 0; i < maxFields; i++) {
		device->fields[i].field = NULL;
	}

	comm->initialized = 0;
	comm->index = 0;
	comm->state = 0;
	comm->send = send;

	device->name = uname;

	//sendInitPacket(device);

	return device;
}

void setDeviceCName(char* name, Device* device) {
	device->cname = name;

	if (device->comm.initialized) {
		sendCName(device);
	}
}

void setDeviceLocation(unsigned char room, unsigned int x, unsigned int y,
		unsigned char icon, Device* device) {
	device->roomId = room;
	device->x = x;
	device->y = y;
	device->icon = icon;

	if (device->comm.initialized) {
		sendLoc(device);
	}
}

int addField(FieldType type, char* name, unsigned int id,
		unsigned char writable, unsigned char vol, Device* device) {
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].field == NULL) {
			device->fields[i].type = type;
			device->fields[i].writable = writable;
			device->fields[i].name = name;
			device->fields[i].id = id;
			device->fields[i].vol = vol;
			device->fields[i].changed = 0;
			device->fields[i].listener = NULL;
			switch (type) {
			case BOOL:
				device->fields[i].field = malloc(sizeof(BoolField));
				break;
			case INT:
				device->fields[i].field = malloc(sizeof(IntField));
				break;
			case FLOAT:
			case FIXED:
				device->fields[i].field = malloc(sizeof(FixedField));
				break;
			case STRING:
				device->fields[i].field = malloc(sizeof(StringField));
				break;
			}
			if (device->comm.initialized) {
				sendField(device, device->fields + i);
			}
			return i;
		}
	}
	return -1;
}

unsigned char hasChanged(unsigned int id, Device* device) {
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			if (device->fields[i].changed) {
				device->fields[i].changed = 0;
				return 1;
			} else {
				return 0;
			}
		}
	}
	return 0;
}

unsigned char getBoolVal(unsigned int id, Device* device) {
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			BoolField* bool = device->fields[i].field;
			return bool->value;
		}
	}
	return 0;
}

unsigned int getIntVal(unsigned int id, Device* device) {
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			IntField* ival = device->fields[i].field;
			return ival->value;
		}
	}
	return 0;
}

unsigned int getFixedVal(unsigned int id, Device* device) {
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			FixedField* fval = device->fields[i].field;
			return fval->value;
		}
	}
	return 0;
}

char* getStringVal(unsigned int id, Device* device) {
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			StringField* sval = device->fields[i].field;
			return sval->value;
		}
	}
	return 0;
}

void setBoolVal(unsigned int id, unsigned char value, Device* device) {
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			BoolField* field = device->fields[i].field;
			field->value = value;
		}
	}
}

void setIntVal(unsigned int id, unsigned int value, Device* device) {
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			IntField* field = device->fields[i].field;
			field->value = value;
		}
	}
}

void setFixedVal(unsigned int id, unsigned int value, unsigned int one,
		Device* device) {
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			FixedField* field = device->fields[i].field;
			field->value = value;
		}
	}
}

void setStringVal(unsigned int id, char* value, Device* device) {
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			StringField* field = device->fields[i].field;
			field->value = value;
		}
	}
}

void setChangeListener(unsigned int id, FieldList listener, Device* device) {
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			device->fields[i].listener = listener;
		}
	}
}
