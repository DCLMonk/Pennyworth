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
 * Packet.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */
#include "Packet.h"
#include <stdio.h>
#include <stdlib.h>
namespace dvs {

Communicator* currentCommunicator = NULL;

Packet::Packet(unsigned char *data) {
//	printf("Data Packet %d\n", data[3]);
	this->data = data;
	this->length = data[0] + 1;
	this->device = (((unsigned int) data[2]) << 8) | data[1];
	allocated = false;
}
Packet::Packet(unsigned int length, unsigned int device, unsigned char pid) {
//	printf("Other Packet %d %d\n", pid, device);
	this->length = length;
	this->device = device;
	this->data = (unsigned char *) malloc(sizeof(unsigned char) * length);
	this->pid = pid;
	if (this->data) {
		this->data[0] = length - 1;
		this->data[1] = device & 0xff;
		this->data[2] = (device >> 8) & 0xff;
		this->data[3] = pid;
		this->allocated = false;
	} else {
		perror("Memory Allocation Failed:");
		this->data = NULL;
		this->length = 0;
		this->allocated = false;
	}
}

Packet::~Packet() {
	if (allocated) {
		free(data);
		data = NULL;
	}
}

inline Device* Packet::getDevice() {
	return Device::getDevice(device);
}

void Packet::send() {
	getDevice()->send(this);
}

unsigned char Packet::getType() {
	return pid;
}

unsigned char *Packet::getData() {
	return data;
}

unsigned int Packet::getLength() {
	return length;
}

} /* namespace DVS */
