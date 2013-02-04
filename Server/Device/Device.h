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
 * Device.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include <stdio.h>
#include <map>
#include <string>

#include "../Room.h"
#include "../Server.h"
#include "Field/Field.h"
using namespace std;

namespace dvs {

class Device;
class Communicator;
class Packet;

extern map<int, Device*> devicesById;
extern map<string, Device*> devicesByString;
extern unsigned int maxDeviceId;

class Device {
public:
	static int allocateDeviceId() {
		return maxDeviceId++;
	}

	static Device *getDevice(int id) {
		return devicesById[id];
	}

	static Device *getDevice(string name) {
		return devicesByString[name];
	}

	static void remDevice(int id) {
		devicesByString[devicesById[id]->getName()] = NULL;
		devicesById[id] = NULL;
		unsigned int nmax;
		for (unsigned int i = 0; i < maxDeviceId; i++) {
			if (devicesById[i] != NULL) {
				nmax = i + 1;
			}
		}
		if (nmax < maxDeviceId) {
			maxDeviceId = nmax;
		}
	}

	static Device *getDevice(Communicator* comm, string name) {
		if (devicesByString.find(name) != devicesByString.end()) {
			return devicesByString[name];
		}
		return new Device(comm, name);
	}

	static void setDevice(int id, string name, Device* device) {
		devicesById[id] = device;
		devicesByString[name] = device;
	}

	Device(Communicator* comm, string name);

	Device();

	virtual ~Device();

	unsigned int getId();

	void setCName(string name);

	string getName();

	string getCName();

	void send(Packet* packet);

	Room* getRoom();

	void setRoom(unsigned int roomId);

	void setLoc(float x, float y);

	void setIcon(unsigned int icon);

	unsigned int getIcon();
	float getX();
	float getY();

	bool hasField(unsigned char id);

	Field* getField(unsigned char id);

	void setField(unsigned char id, Field* field);

	unsigned int getMaxField();

	void setComm(Communicator* comm);

	int getNFields();

	Communicator* getComm();

	void setMaxLength(unsigned int length) {
		this->maxLength = length;
	}

	unsigned int getMaxLength() {
		return maxLength;
	}

protected:
	map<unsigned char, Field*>* fields;
	unsigned int deviceId;
	int roomId;
	unsigned int maxField;
	string name;
	string cname;
	Communicator* comm;
	float x, y;
	unsigned int icon;
	unsigned int maxLength;
};

} /* namespace DVS */
#endif /* DEVICE_H_ */
