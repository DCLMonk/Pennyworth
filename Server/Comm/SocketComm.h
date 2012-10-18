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
 * SocketComm.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef SOCKETCOMM_H_
#define SOCKETCOMM_H_

#include "Communicator.h"
namespace dvs {

class SocketComm: public Communicator {
public:
	SocketComm(int fd);
	SocketComm();

	~SocketComm();

	void writeBytes(unsigned char* data, unsigned int length);

	int readBytes(unsigned char* data, unsigned int length);

	void remove();
protected:
	int fd;
};

} /* namespace dvs */

#endif /* SOCKETCOMM_H_ */
