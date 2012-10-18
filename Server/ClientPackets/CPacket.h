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
 * CPacket.h
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#ifndef CPACKET_H_
#define CPACKET_H_

#include <string>
#include <sstream>
#include <vector>
#include "User.h"

using namespace std;

namespace dvs {

class CCommunicator;

extern CCommunicator* currentCCommunicator;

class CPacket {
public:
	static CCommunicator* getCurrentComm() {
		return currentCCommunicator;
	}

	static void setCurrentComm(CCommunicator* comm) {
		currentCCommunicator = comm;
	}

	CPacket(string data);
	CPacket(unsigned int id, User* user);
	virtual ~CPacket();

	string toString();
	virtual void streamData(stringstream& data);

	void send();

protected:
	User* user;
	unsigned int id;
	vector<string>* args;
};

typedef enum {
	LOGIN=1,
	UID=2,
	LOGIN_FAILED=3,
	GET_DEVICES=4,
	DEVICE_DEF=5,
	GET_FIELDS=6,
	FIELD_INFO=7,
	GET_FIELD=8,
	SEND_FIELD=9,
	SET_FIELD=10,
	COMMAND=11
} CPacketTypes;

}

#include "LoginPacket.h"
#include "UIDPacket.h"
#include "LoginFailurePacket.h"
#include "GetDevicesPacket.h"
#include "DeviceDefPacket.h"
#include "GetFieldsPacket.h"
#include "FieldInfoPacket.h"
#include "CGetFieldPacket.h"
#include "SendFieldPacket.h"
#include "CCommandPacket.h"
#include "CSetFieldPacket.h"

#endif /* CPACKET_H_ */
