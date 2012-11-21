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
 * LoginFailurePacket.h
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#ifndef LOGINFAILUREPACKET_H_
#define LOGINFAILUREPACKET_H_

#include "CPacket.h"

namespace dvs {

class LoginFailurePacket: public dvs::CPacket {
public:
	LoginFailurePacket(string error, CCommunicator* comm);
	virtual ~LoginFailurePacket();

	void streamData(stringstream& data);
private:
	string error;
};

} /* namespace dvs */
#endif /* LOGINFAILUREPACKET_H_ */
