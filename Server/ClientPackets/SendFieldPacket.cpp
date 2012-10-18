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
 * SendFieldPacket.cpp
 *
 *  Created on: Jul 5, 2012
 *      Author: jmonk
 */

#include "SendFieldPacket.h"

namespace dvs {

SendFieldPacket::SendFieldPacket(Field* field, User* user) : CPacket(SEND_FIELD, user) {
	this->field = field;
}

SendFieldPacket::~SendFieldPacket() {

}

void SendFieldPacket::streamData(stringstream& data) {
	data << ':';
	data << field->getDevice()->getId();
	data << ':';
	data << field->getId();
	data << ':';
	switch (field->getType()) {
	case BOOL:
		if (((BooleanField*)field)->getBool()) {
			data << "True";
		} else {
			data << "False";
		}
		break;
	case INTEGER:
		data << ((IntegerField*)field)->getInt();
		break;
	case FLOAT:
		data << ((FloatField*)field)->getFloat();
		break;
	case FIXED:
		data << ((FixedField*)field)->getFloat();
		break;
	case STRING:
		data << ((StringField*)field)->getValue();
		break;
	}
}

} /* namespace dvs */
