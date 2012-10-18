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
 * MaxLengthPacket.h
 *
 *  Created on: Jun 26, 2012
 *      Author: jmonk
 */

#ifndef MAXLENGTHPACKET_H_
#define MAXLENGTHPACKET_H_

#include "Packet.h"

namespace dvs {

class MaxLengthPacket: public dvs::Packet {
public:
	MaxLengthPacket(unsigned char* data);
	virtual ~MaxLengthPacket();
};

} /* namespace dvs */
#endif /* MAXLENGTHPACKET_H_ */
