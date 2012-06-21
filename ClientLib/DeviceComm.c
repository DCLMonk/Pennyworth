/*
 * DeviceComm.c
 *
 *  Created on: Jun 21, 2012
 *      Author: jmonk
 */

#include "DeviceClient.h"

enum RecvState {
	INIT = 0,
	INIT1,
	INIT2,
	INIT3,
	START,
	DEV1,
	DEV2,
	TYPE,
	BURN,

	INITP,
	INITCN,
	INITLOC,
	INITFIL,
	GETFIELD,
	FIELDVAL,
	SETFIELD,
	SUBSCRIBE,
	SETONE,
	CUSTOM,
	MAXLEN
};

void sendValue(unsigned char id, Device* device) {
	CommManager* comm = &device->comm;
	FieldDef* field = NULL;
	unsigned int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			field = device->fields + i;
			break;
		}
	}
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
		length = 6 + strlen(*((char**)field->field));
		break;
	}

	comm->send((unsigned char)(length - 1));
	comm->send((unsigned char)(device->deviceId & 0xff));
	comm->send((unsigned char)((device->deviceId>>8) & 0xff));
	comm->send((unsigned char)(6));
	comm->send((unsigned char)(id));

	char* s;
	switch (field->type) {
	case BOOL:
		comm->send(*((unsigned int*)field->field));
		break;
	case INT:
		comm->send((*((unsigned int*)field->field)));
		comm->send((unsigned char)((*((unsigned int*)field->field))>>8));
		comm->send((unsigned char)(0));
		comm->send((unsigned char)(0));
		break;
	case FLOAT:
	case FIXED:
		comm->send((*((unsigned int*)field->field)));
		comm->send((unsigned char)((*((unsigned int*)field->field))>>8));
		break;
	case STRING:
		s = ((char*)(field->field));
		for (i = 0; i < length - 5; i++) {
			comm->send(s[i]);
		}
		break;
	}
}


void readValue(unsigned char id, Device* device) {
	CommManager* comm = &device->comm;
	FieldDef* field = NULL;
	unsigned char* buffer = comm->buffer + 5;
	unsigned int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].id == id) {
			field = device->fields + i;
			break;
		}
	}
	unsigned char* buf;
	switch (field->type) {
	case BOOL:
		buf = ((unsigned char*)field->field);
		buf[0] = buffer[0];
		printf("Set Bool to: %d\n", buf[0]);
		break;
	case INT:
	case FLOAT:
	case FIXED:
		buf = ((unsigned char*)field->field);
		buf[0] = buffer[1];
		buf[1] = buffer[0];
		break;
	case STRING:
		field->field = comm->buffer + 5;
		break;
	}
	field->changed = 1;
	if (field->listener != NULL) {
		field->listener(field);
	}
}

void parsePacket(Device* device) {
	CommManager* comm = &device->comm;
	printf("Parse Packet\n");
	switch (comm->state) {
	case INITCN:// What?
		break;
	case INITLOC:// What?
		break;
	case INITFIL:// What?
		break;
	case GETFIELD:
		sendValue(comm->buffer[4], device);
		break;
	case FIELDVAL:// What?
		break;
	case SETFIELD:
		readValue(comm->buffer[4], device);
		break;
	case SUBSCRIBE:
		device->fields[comm->buffer[4]].subscribed = comm->buffer[5];
		break;
	case SETONE:// What?
		break;
	case MAXLEN:// What?
		break;
	case CUSTOM:// Later
		break;
	case INITP:// What?
	case BURN:
		printf("Init\n");
		if (strcmp(device->name, comm->buffer + 4) == 0) {
			device->deviceId = (((unsigned int) comm->buffer[2]) << 8)
						| comm->buffer[1];
			printf("Match %d\n", device->deviceId);
			sendInitPackets(device);
		}
		break;
	}
}

void sendField(Device* device, FieldDef* field) {
	CommManager* comm = &device->comm;
	unsigned int length = strlen(field->name) + 9;
	printf("Send Field %d\n", length);

	comm->send((unsigned char)(length - 1));
	comm->send((unsigned char)(device->deviceId & 0xff));
	comm->send((unsigned char)((device->deviceId>>8) & 0xff));
	comm->send((unsigned char)(4));
	comm->send((unsigned char)(field->type));
	comm->send((unsigned char)(field->writable));
	comm->send((unsigned char)(field->vol));
	comm->send((unsigned char)(field->id));

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

	// Main Init
	comm->send((unsigned char)(length - 1));
	comm->send((unsigned char)(device->deviceId & 0xff));
	comm->send((unsigned char)((device->deviceId>>8) & 0xff));
	comm->send((unsigned char)(1));
	for (i = 0; i < length - 4; i++) {
		comm->send(device->name[i]);
	}
}

void sendInitPackets(Device* device) {
	printf("Init Packets\n");
	sendCName(device);

	sendLoc(device);

	int i;
	for (i = 0; i < device->nfields; i++) {
		if (device->fields[i].field != NULL) {
			sendField(device, device->fields + i);
		}
	}
	// Max size here
}

void sendLoc(Device* device) {
	printf("Loc\n");
	CommManager* comm = &device->comm;

	// Location
	comm->send((unsigned char)(9));
	comm->send((unsigned char)(device->deviceId & 0xff));
	comm->send((unsigned char)((device->deviceId>>8) & 0xff));
	comm->send((unsigned char)(3));
	printf("Room: %d\n", device->roomId);
	comm->send((unsigned char)(device->roomId));
	comm->send((unsigned char)(device->x & 0xff));
	comm->send((unsigned char)((device->x>>8) & 0xff));
	comm->send((unsigned char)(device->y & 0xff));
	comm->send((unsigned char)((device->y>>8) & 0xff));
	comm->send((unsigned char)(device->icon));
}

void sendCName(Device* device) {
	printf("CName\n");
	CommManager* comm = &device->comm;

	// Common Name
	unsigned int length = strlen(device->cname) + 5;
	unsigned int i;

	comm->send((unsigned char)(length - 1));
	comm->send((unsigned char)(device->deviceId & 0xff));
	comm->send((unsigned char)((device->deviceId>>8) & 0xff));
	comm->send((unsigned char)(2));
	for (i = 0; i < length - 4; i++) {
		comm->send(device->cname[i]);
	}
}

void recvChar(char c, Device* device) {
	CommManager* comm = &device->comm;
	comm->buffer[comm->index++] = c;
	unsigned int did;

	printf("R\n");

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
		did = (((unsigned int) comm->buffer[2]) << 8)
				| comm->buffer[1];
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


