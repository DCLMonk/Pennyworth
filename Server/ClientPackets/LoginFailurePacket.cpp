/*
 * LoginFailurePacket.cpp
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#include "LoginFailurePacket.h"

namespace dvs {

LoginFailurePacket::LoginFailurePacket(string error) : CPacket(LOGIN_FAILED, NULL) {
	this->error = error;
}

LoginFailurePacket::~LoginFailurePacket() {

}

void LoginFailurePacket::streamData(stringstream& data) {
	data << ':';
	data << error;
}

} /* namespace dvs */
