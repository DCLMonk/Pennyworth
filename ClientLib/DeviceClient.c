/*
 * DeviceClient.c
 *
 *  Created on: Jun 19, 2012
 *      Author: jmonk
 */

#include "DeviceClient.h"
#define NULL (0)

enum RecvState {
	INIT,

};

Device* createDevice(char* uname, int maxFields, SendRoutine send) {
	Device* device = malloc(sizeof(Device));
	int i;

	device->fields = malloc(maxFields * sizeof(FieldDef));
	device->nfields = maxFields;
	for (i = 0; i < maxFields; i++) {
		device->fields[i].field = NULL;
	}

	device->comm.initialized = 0;
	device->comm.index = 0;
	device->comm.state = INIT;
	device->comm.send = send;

	device->name = uname;

	return device;
}

void setDeviceCName(char* name, Device* device){
	device->cname = name;
}

void setDeviceLocation(unsigned int room, unsigned int x, unsigned int y,
								unsigned int icon, Device* device){
	device->roomId = room;
	device->x = x;
	device->y = y;
	device->icon = icon;
}

int addField(FieldType type, char* name, unsigned int id,
		unsigned char writable, unsigned char vol, Device* device){
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
			case FIXED:
				device->fields[i].field = malloc(sizeof(FixedField));
				break;
			case STRING:
				device->fields[i].field = malloc(sizeof(StringField));
				break;
			}
		}
	}
	return -1;
}

unsigned char hasChanged(unsigned int id, Device* device){
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

unsigned char getBoolVal(unsigned int id, Device* device){
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			BoolField* bool = device->fields[i].field;
			return bool.value;
		}
	}
	return 0;
}

unsigned int getIntVal(unsigned int id, Device* device){
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			IntField* ival = device->fields[i].field;
			return ival.value;
		}
	}
	return 0;
}

unsigned int getFixedVal(unsigned int id, Device* device){
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			FixedField* fval = device->fields[i].field;
			return fval.value;
		}
	}
	return 0;
}

char* getStringVal(unsigned int id, Device* device){
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			StringField* sval = device->fields[i].field;
			return sval.value;
		}
	}
	return 0;
}

void setBoolVal(unsigned int id, unsigned char value, Device* device){
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			BoolField field = device->fields[i].field;
			field.value = value;
		}
	}
}

void setIntVal(unsigned int id, unsigned int value, Device* device){
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			IntField field = device->fields[i].field;
			field.value = value;
		}
	}
}

void setFixedVal(unsigned int id, unsigned int value, unsigned int one, Device* device){
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			FixedField field = device->fields[i].field;
			field.value = value;
		}
	}
}

void setStringVal(unsigned int id, char* value, Device* device){
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			StringField field = device->fields[i].field;
			field.value = value;
		}
	}
}

void setChangeListener(unsigned int id, FieldList listener, Device* device){
	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			device->fields[i].listener = listener;
		}
	}
}

void recvChar(char c, Device* device){
	switch (device->comm.state) {
	case INIT:
		break;
	}
}
