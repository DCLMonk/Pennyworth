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
 * CCommunicator.h
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#ifndef CCOMMUNICATOR_H_
#define CCOMMUNICATOR_H_

#include <string>
#include <vector>
#include "Runnable.h"
#include "CPacket.h"
#include "PacketListener.h"

namespace dvs {

#define BUF_LENGTH 256

class User;

class CCommunicator {
public:
	CCommunicator();
	virtual ~CCommunicator();

	void sendPacket(CPacket* packet);
	void getPacket();

	void makePacket(std::string packet);

	virtual void writeBytes(const char* data, unsigned int length);

	virtual int readBytes(char* data, unsigned int length);

	unsigned int getId();

	void setId(int id);

	void send(CPacket* packet);

	void callback(int id, CPacket* packet);

	void registerListener(CPacketTypes type, void* data, Listener listener);

protected:
	std::vector<PacketListener*> listeners;
	char buffer[BUF_LENGTH];
	char pbuffer[BUF_LENGTH];
	unsigned int index;
	int id;
};

class CCommHandler: public Runnable {
public:
	CCommHandler(CCommunicator* comm) {
		this->comm = comm;
	}

	~CCommHandler() {
		delete comm;
	}

	void run() {
//		CPacket::setCurrentComm(comm);
		(comm)->getPacket();
	}
private:
	CCommunicator* comm;
};

}

#endif /* CCOMMUNICATOR_H_ */
