/*
 * DeviceComm.c
 *
 *  Created on: Jun 21, 2012
 *      Author: jmonk
 */

#include "DeviceClient.h"
#include "DeviceComm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define printf(x, ...)

enum RecvState {
	INIT = 20,
	INIT1 = 21,
	INIT2 = 22,
	INIT3 = 23,
	START = 24,
	DEV1 = 25,
	DEV2 = 26,
	TYPE = 27,
	BURN = 28,

	STARTP = 0,
	INITP = 1,
	INITCN = 2,
	INITLOC = 3,
	INITFIL = 4,
	GETFIELD = 5,
	FIELDVAL = 6,
	SETFIELD = 7,
	SUBSCRIBE = 8,
	SETONE = 9,
	CUSTOM,
	MAXLEN
};

FieldDef* getField(unsigned int id, Device* device) {
	unsigned int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			return &device->fields[i];
		}
	}
	return NULL;
}


void sendOnePacket(unsigned int id, Device* device) {
	CommManager* comm = &device->comm;
	unsigned int length = 7;
	FixedField* fixed = (FixedField*)getField(id, device)->field;

	// Main Init
	comm->send((unsigned char) (length - 1));
	comm->send((unsigned char) (device->deviceId & 0xff));
	comm->send((unsigned char) ((device->deviceId >> 8) & 0xff));
	comm->send((unsigned char) (9));
	comm->send((unsigned char) (id));
	comm->send((unsigned char) (fixed->one & 0xff));
	comm->send((unsigned char) ((fixed->one >> 8) & 0xff));
	printf("Sending One Value %d %d\n", (fixed->one & 0xff), ((fixed->one >> 8) & 0xff));
}

void sendValue(unsigned char id, Device* device) {
	CommManager* comm = &device->comm;
	FieldDef* field = getField(id, device);
	unsigned int i;
	printf("Sending Field %s Value\n", field->name);
	unsigned int length = 0;
	switch (field->type) {
	case BOOL:
		length = 6;
		break;
	case INT:
		length = 9;
		break;
	case FLOAT:
	case FIXED:
		length = 7;
		break;
	case STRING:
		length = 6 + strlen(*((char**) field->field));
		break;
	}

	comm->send((unsigned char) (length - 1));
	comm->send((unsigned char) (device->deviceId & 0xff));
	comm->send((unsigned char) ((device->deviceId >> 8) & 0xff));
	comm->send((unsigned char) (6));
	comm->send((unsigned char) (id));

	char* s;
	switch (field->type) {
	case BOOL:
		comm->send(*((unsigned int*) field->field));
		break;
	case INT:
		comm->send((*((unsigned int*) field->field)));
		comm->send((unsigned char) ((*((unsigned int*) field->field)) >> 8));
		comm->send((unsigned char) (0));
		comm->send((unsigned char) (0));
		break;
	case FLOAT:
	case FIXED:
		comm->send((*((unsigned int*) field->field)));
		comm->send((unsigned char) ((*((unsigned int*) field->field)) >> 8));
		sendOnePacket(id, device);
		break;
	case STRING:
		s = ((char*) (field->field));
		for (i = 0; i < length - 5; i++) {
			comm->send(s[i]);
		}
		break;
	}
}

void readValue(unsigned char id, Device* device) {
	CommManager* comm = &device->comm;
	FieldDef* field = getField(id, device);
	printf("Reading Field %s Value\n", field->name);
	char* buffer = comm->buffer + 5;
	unsigned int i;
	StringField* s;
	FixedField* f;
	IntField* ifd;

	unsigned char* buf;
	switch (field->type) {
	case BOOL:
		buf = ((unsigned char*) field->field);
		buf[0] = buffer[0];
		printf("Set Bool to: %d\n", buf[0]);
		break;
	case INT:
		ifd = (IntField*)field->field;
		ifd->value = (((unsigned int)buffer[1]) << 8) | buffer[0];
		printf("Set Int to: %d\n", ifd->value);
		break;
	case FLOAT:
	case FIXED:
		f = (FixedField*)field->field;
		f->value = (((unsigned int)buffer[1]) << 8) | buffer[0];
		printf("Set Float to: %d\n", f->value);
		break;
	case STRING:
		s = (StringField*)field->field;
		if (s->value != NULL) {
			free(s->value);
		}
		s->value = (char*)malloc(sizeof(char) * (strlen(comm->buffer + 5) + 1));
		for (i = 0; i < (strlen(comm->buffer + 5) + 1); i++) {
			s->value[i] = comm->buffer[i + 5];
		}
		printf("Set String to: %s\n", s->value);
		break;
	}
	field->changed = 1;
	if (field->listener != NULL) {
		field->listener(field);
	}
}

void sendField(Device* device, FieldDef* field) {
	CommManager* comm = &device->comm;
	unsigned int length = strlen(field->name) + 9;
	printf("Send Field %d\n", length);
	printf("Defining Field %s Value\n", field->name);

	comm->send((unsigned char) (length - 1));
	comm->send((unsigned char) (device->deviceId & 0xff));
	comm->send((unsigned char) ((device->deviceId >> 8) & 0xff));
	comm->send((unsigned char) (4));
	comm->send((unsigned char) (field->type));
	comm->send((unsigned char) (field->writable));
	comm->send((unsigned char) (field->vol));
	comm->send((unsigned char) (field->id));

	unsigned int i;
	for (i = 0; i < length - 8; i++) {
		comm->send(field->name[i]);
	}
	sendValue(field->id, device);
}

void sendInitPacket(Device* device) {
	CommManager* comm = &device->comm;
	unsigned int length = strlen(device->name) + 5;
	unsigned int i;
	printf("Sending Device Init\n");

	// Main Init
	comm->send((unsigned char) (length - 1));
	comm->send((unsigned char) (device->deviceId & 0xff));
	comm->send((unsigned char) ((device->deviceId >> 8) & 0xff));
	comm->send((unsigned char) (1));
	for (i = 0; i < length - 4; i++) {
		comm->send(device->name[i]);
	}
}

void sendInitPackets(Device* device) {
	sendCName(device);

	sendLoc(device);

	unsigned int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].field != NULL) {
			sendField(device, device->fields + i);
		}
	}
	CommManager* comm = &device->comm;

#if BUFFER_LENGTH != 256
	comm->send((unsigned char) (4));
	comm->send((unsigned char) (device->deviceId & 0xff));
	comm->send((unsigned char) ((device->deviceId >> 8) & 0xff));
	comm->send((unsigned char) (10));
	comm->send((unsigned char) (BUFFER_LENGTH));
#endif
}

void sendLoc(Device* device) {
	printf("Sending Location\n");
	CommManager* comm = &device->comm;

	// Location
	comm->send((unsigned char) (9));
	comm->send((unsigned char) (device->deviceId & 0xff));
	comm->send((unsigned char) ((device->deviceId >> 8) & 0xff));
	comm->send((unsigned char) (3));
	printf("Room: %d\n", device->roomId);
	comm->send((unsigned char) (device->roomId));
	comm->send((unsigned char) (device->x & 0xff));
	comm->send((unsigned char) ((device->x >> 8) & 0xff));
	comm->send((unsigned char) (device->y & 0xff));
	comm->send((unsigned char) ((device->y >> 8) & 0xff));
	comm->send((unsigned char) (device->icon));
}

void sendCName(Device* device) {
	printf("Sending CName\n");
	CommManager* comm = &device->comm;

	// Common Name
	unsigned int length = strlen(device->cname) + 5;
	unsigned int i;

	comm->send((unsigned char) (length - 1));
	comm->send((unsigned char) (device->deviceId & 0xff));
	comm->send((unsigned char) ((device->deviceId >> 8) & 0xff));
	comm->send((unsigned char) (2));
	for (i = 0; i < length - 4; i++) {
		comm->send(device->cname[i]);
	}
}

void parsePacket(Device* device) {
	CommManager* comm = &device->comm;
	printf("Parse Packet %d\n", comm->buffer[3]);
	switch (comm->state) {
	case INITCN: // What?
		break;
	case INITLOC: // What?
		break;
	case INITFIL: // What?
		break;
	case GETFIELD:
		sendValue(comm->buffer[4], device);
		break;
	case FIELDVAL: // What?
		break;
	case SETFIELD:
		readValue(comm->buffer[4], device);
		break;
	case SUBSCRIBE:
		device->fields[(int)comm->buffer[4]].subscribed = comm->buffer[5];
		break;
	case SETONE: // What?
		break;
	case MAXLEN: // What?
		break;
	case CUSTOM: // Later
		break;
	case INITP: // What?
		printf("Init Device\n");
	case BURN:
		if ((comm->buffer[3] == 0) && (comm->buffer[2] == 0) && (comm->buffer[1] == 0)) {
			comm->initialized = 1;
			sendInitPacket(device);
			comm->state = START;
			comm->index = 0;
			printf("Comm Initialized\n");
		}
		if (comm->buffer[3] == 1) {
			if (strcmp(device->name, comm->buffer + 4) == 0) {
				device->deviceId = (((unsigned int) comm->buffer[2]) << 8)
							| comm->buffer[1];
				printf("New Device Id: %d\n", device->deviceId);
				sendInitPackets(device);
			}
		}
		break;
	}
}

void recvChar(char c, Device* device) {
	CommManager* comm = &device->comm;
	comm->buffer[comm->index++] = c;
	unsigned int did;

	switch (comm->state) {
	case INIT:
		if (c == 3) {
			comm->index = 0;
			comm->state = INIT1;
		}
		comm->index = 0;
		break;
	case INIT1:
		if (c == 0) {
			comm->state = INIT2;
		} else {
			comm->state = INIT;
		}
		break;
	case INIT2:
		if (c == 0) {
			comm->state = INIT3;
		} else {
			comm->state = INIT;
		}
		break;
	case INIT3:
		if (c == 0) {
			comm->initialized = 1;
			sendInitPacket(device);
			comm->state = START;
			comm->index = 0;
			printf("Comm Initialized\n");
		} else {
			comm->state = INIT;
		}
		break;
	case START:
		comm->length = (unsigned) c;
		comm->state = DEV1;
		break;
	case DEV1:
		comm->state = DEV2;
		break;
	case DEV2:
		did = (((unsigned int) comm->buffer[2]) << 8) | comm->buffer[1];
		if (did == device->deviceId) {
			comm->state = TYPE;
		} else {
			comm->state = BURN;
		}
		break;
	case TYPE:
		if (((unsigned) c) < 250) {
			comm->state = INITP + c - 1;
		} else {
			comm->state = CUSTOM;
		}
		break;
	case BURN:
		if (comm->index == BUFFER_LENGTH) {
			comm->index = 0;
			comm->length -= BUFFER_LENGTH;
		 }
	case STARTP:
	case INITP:
	case INITCN:
	case INITLOC:
	case INITFIL:
	case GETFIELD:
	case FIELDVAL:
	case SETFIELD:
	case SUBSCRIBE:
	case SETONE:
	case MAXLEN:
	case CUSTOM:
		if (comm->index == comm->length + 1) {
			parsePacket(device);
			comm->state = START;
			comm->index = 0;
		}
		break;
	}
}

