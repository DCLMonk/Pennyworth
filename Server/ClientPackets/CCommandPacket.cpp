/*
 * CCommandPacket.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: jmonk
 */

#include "CCommandPacket.h"
#include "CommandInterface.h"
#include <stdio.h>

void buf_putch(char c) {

}

namespace dvs {

CCommandPacket::CCommandPacket(std::string data) : CPacket(data) {
	if (this->args->size() >= 3) {
		buffer[0] = '\0';
		instance->commandHandle((char *)(*args)[2].c_str(), buffer, 2048);
		this->send();
	}
}

CCommandPacket::~CCommandPacket() {

}

void CCommandPacket::streamData(stringstream& data) {
	for (int i = 0; i < 2048; i++) {
		if (buffer[i] == ':') buffer[i] = ';';
		if (buffer[i] == '\n') buffer[i] = '\f';
	}

	string out(buffer);

	data << ':';
	data << out;
}

} /* namespace dvs */
