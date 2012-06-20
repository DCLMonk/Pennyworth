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
using namespace std;
#include <string>

#include "../Room.h"
#include "../Server.h"
#include "Field/Field.h"

namespace dvs {

class Device;
class Communicator;
class Packet;

extern map<int, Device*> devicesById;
extern map<string, Device*> devicesByString;

class Device {
public:
	static int allocateDeviceId() {
		static unsigned int maxDeviceId = 0;
		return maxDeviceId++;
	}

	static Device *getDevice(int id) {
		return devicesById[id];
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

	bool hasField(unsigned char id);

	Field* getField(unsigned char id);

	void setField(unsigned char id, Field* field);

protected:
	map<unsigned char, Field*> fields;
	unsigned int deviceId;
	unsigned int roomId;
	string name;
	string cname;
	Communicator* comm;
	float x, y;
	unsigned int icon;
};

} /* namespace DVS */
#endif /* DEVICE_H_ */
