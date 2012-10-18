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
 * Communicator.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef COMMUNICATOR_H_
#define COMMUNICATOR_H_

#include "Packet.h"
#include <vector>

namespace dvs {

class Communicator {
public:
	Communicator();
	virtual ~Communicator();

	void sendPacket(Packet* packet);
	void getPacket();

	void makePacket();

	virtual void writeBytes(unsigned char* data, unsigned int length);

	virtual int readBytes(unsigned char* data, unsigned int length);

	virtual void remove();

	string toString();

	unsigned int commId;
protected:
	void makeStart();
	void makeInit();
	void makeInitCName();
	void makeInitLoc();
	void makeInitField();
	void makeGetField();
	void makeFieldValue();
	void makeSetField();
	void makeSubscribe();
	void makeSetOne();
	void makeMaxLength();

	unsigned char buffer[256];
	unsigned int size;
	unsigned int index;
	string name;
};

class CommHandler: public Runnable {
public:
	CommHandler(Communicator* comm) {
		this->comm = comm;
	}

	~CommHandler() {
		delete comm;
	}

	void run() {
		Packet::setCurrentComm(comm);
		(comm)->getPacket();
	}
private:
	Communicator* comm;
};

} /* namespace dvs */

extern std::vector<dvs::Communicator*> comms;
#endif /* COMMUNICATOR_H_ */
