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
 * DeviceClient.c
 *
 *  Created on: Jun 19, 2012
 *      Author: jmonk
 */

#include "DeviceClient.h"
#include "DeviceComm.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void sendLoc(Device* device);
void sendCName(Device* device);
void sendField(Device* device, FieldDef* field);
void sendValue(unsigned char id, Device* device);
void sendInitPackets(Device* device);

Device* createDevice(char* uname, int maxFields, SendRoutine send) {
	Device* device = (Device*)malloc(sizeof(Device));
	CommManager* comm = &device->comm;
	int i;

	device->fields = (FieldDef*)malloc(maxFields * sizeof(FieldDef));
	device->nfields = maxFields;
	for (i = 0; i < maxFields; i++) {
		device->fields[i].field = NULL;
	}

	comm->initialized = 0;
	comm->index = 0;
	comm->state = 20;
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
	unsigned int i;
	BoolField* b;
	IntField* ifd;
	FixedField* f;
	StringField* s;
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
				b = (BoolField*)device->fields[i].field;
				b->value = 0;
				break;
			case INT:
				device->fields[i].field = malloc(sizeof(IntField));
				ifd = (IntField*)device->fields[i].field;
				ifd->value = 0;
				break;
			case FLOAT:
			case FIXED:
				device->fields[i].field = malloc(sizeof(FixedField));
				f = (FixedField*)device->fields[i].field;
				f->value = 0;
				f->one = 1;
				break;
			case STRING:
				device->fields[i].field = malloc(sizeof(StringField));
				s = (StringField*)device->fields[i].field;
				s->value = (char*)malloc(1 * sizeof(char));
				s->value[0] = '\0';
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
	unsigned int i;
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
	unsigned int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			BoolField* b = (BoolField*)device->fields[i].field;
			return b->value;
		}
	}
	return 0;
}

unsigned int getIntVal(unsigned int id, Device* device) {
	unsigned int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			IntField* ival = (IntField*)device->fields[i].field;
			return ival->value;
		}
	}
	return 0;
}

unsigned int getFixedVal(unsigned int id, Device* device) {
	unsigned int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			FixedField* fval = (FixedField*)device->fields[i].field;
			return fval->value;
		}
	}
	return 0;
}

char* getStringVal(unsigned int id, Device* device) {
	unsigned int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			StringField* sval = (StringField*)device->fields[i].field;
			return sval->value;
		}
	}
	return 0;
}

void setBoolVal(unsigned int id, unsigned char value, Device* device) {
	FieldDef* fieldDef = getField(id, device);
	BoolField* field;
	if (fieldDef != NULL) {
		field = (BoolField*)fieldDef->field;
		field->value = value;
		if (fieldDef->subscribed && device->comm.initialized) {
			sendField(device, fieldDef);
		}
	}
}

void setIntVal(unsigned int id, unsigned int value, Device* device) {
	FieldDef* fieldDef = getField(id, device);
	IntField* field;
	if (fieldDef != NULL) {
		field = (IntField*)fieldDef->field;
		field->value = value;
		if (fieldDef->subscribed && device->comm.initialized) {
			sendField(device, fieldDef);
		}
	}
}

void setFixedVal(unsigned int id, unsigned int value,
		Device* device) {
	FieldDef* fieldDef = getField(id, device);
	FixedField* field;
	if (fieldDef != NULL) {
		field = (FixedField*)fieldDef->field;
		field->value = value;
		if (fieldDef->subscribed && device->comm.initialized) {
			sendField(device, fieldDef);
		}
	}
}

void setStringVal(unsigned int id, char* value, Device* device) {
	FieldDef* fieldDef = getField(id, device);
	StringField* field;
	unsigned int i;
	if (fieldDef != NULL) {
		field = (StringField*)fieldDef->field;
		if (field->value != NULL) {
			free(field->value);
		}
		if (value != NULL) {
			field->value = (char*)malloc(sizeof(char) * (strlen(value) + 1));
			for (i = 0; i < (strlen(value) + 1); i++) {
				field->value[i] = value[i];
			}
		} else {
			field->value = NULL;
		}
		if (fieldDef->subscribed && device->comm.initialized) {
			sendField(device, fieldDef);
		}
	}
}

void setChangeListener(unsigned int id, FieldList listener, Device* device) {
	unsigned int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			device->fields[i].listener = listener;
		}
	}
}

void setOneVal(unsigned int id, unsigned int one, Device* device) {
	FixedField* fixed = (FixedField*)getField(id, device)->field;
	fixed->one = one;

	if (device->comm.initialized) {
		sendOnePacket(id, device);
	}
}

unsigned int shouldBreak(Device* device) {
	return device->comm.shouldBreak;
}
