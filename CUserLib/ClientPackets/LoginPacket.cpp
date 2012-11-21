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
 * LoginPacket.cpp
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#include "LoginPacket.h"
#include "LoginFailurePacket.h"
#include "User.h"
#include "UIDPacket.h"
#include "CCommunicator.h"

namespace dvs {

LoginPacket::LoginPacket(string user, string pass, CCommunicator* comm) : CPacket(LOGIN, comm) {
//	if (args->size() >= 4) {
//		string user = (*args)[2];
//		string pass = (*args)[3];
//		if (Server::isValid(user, pass)) {
//			User* user = Server::newUser(CPacket::getCurrentComm());
//			UIDPacket uidPacket(user);
//			uidPacket.send();
//		} else {
//			LoginFailurePacket loginFailure("Invalid Username and/or Password");
//			CPacket::getCurrentComm()->sendPacket(&loginFailure);
//		}
//	} else {
//		// TODO: Start dealing with device and client errors
//		printf("Client Error %d\n", (int)args->size());
//	}
}

LoginPacket::~LoginPacket() {

}

} /* namespace dvs */