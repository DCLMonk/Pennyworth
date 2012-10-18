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
 * DeviceComm.h
 *
 *  Created on: Jun 21, 2012
 *      Author: jmonk
 */

#ifndef DEVICECOMM_H_
#define DEVICECOMM_H_

#define printf(x,...)

FieldDef* getField(unsigned int id, Device* device);

void sendLoc(Device* device);

void sendCName(Device* device);

void sendField(Device* device, FieldDef* field);

void sendValue(unsigned char id, Device* device);

void readValue(unsigned char id, Device* device);

void sendInitPackets(Device* device);

void sendOnePacket(unsigned int id, Device* device);

#endif /* DEVICECOMM_H_ */
