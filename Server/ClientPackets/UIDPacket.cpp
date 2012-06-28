/*
 * UIDPacket.cpp
 *
 *  Created on: Jun 27, 2012
 *      Author: jmonk
 */

#include "UIDPacket.h"
#include <stdio.h>

namespace dvs {

UIDPacket::UIDPacket(User* user) : CPacket(UID, user) {

}

UIDPacket::~UIDPacket() {

}

void UIDPacket::streamData(stringstream& data) {

}

} /* namespace dvs */
