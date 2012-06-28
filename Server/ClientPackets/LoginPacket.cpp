/*
 * LoginPacket.cpp
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#include "LoginPacket.h"
#include "LoginFailurePacket.h"
#include "Server.h"
#include "User.h"
#include "UIDPacket.h"
#include "CCommunicator.h"

namespace dvs {

LoginPacket::LoginPacket(string data) : CPacket(data) {
	if (args->size() >= 4) {
		string user = (*args)[2];
		string pass = (*args)[3];
		if (Server::isValid(user, pass)) {
			User* user = Server::newUser(CPacket::getCurrentComm());
			UIDPacket uidPacket(user);
			uidPacket.send();
		} else {
			LoginFailurePacket loginFailure("Invalid Username and/or Password");
			CPacket::getCurrentComm()->sendPacket(&loginFailure);
		}
	} else {
		// TODO: Start dealing with device and client errors
		printf("Client Error %d\n", args->size());
	}
}

LoginPacket::~LoginPacket() {

}

} /* namespace dvs */
