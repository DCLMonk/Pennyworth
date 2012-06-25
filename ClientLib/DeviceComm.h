/*
 * DeviceComm.h
 *
 *  Created on: Jun 21, 2012
 *      Author: jmonk
 */

#ifndef DEVICECOMM_H_
#define DEVICECOMM_H_

//#define printf(x,...)

FieldDef* getField(unsigned int id, Device* device);

void sendLoc(Device* device);

void sendCName(Device* device);

void sendField(Device* device, FieldDef* field);

void sendValue(unsigned char id, Device* device);

void readValue(unsigned char id, Device* device);

void sendInitPackets(Device* device);

void sendOnePacket(unsigned int id, Device* device);

#endif /* DEVICECOMM_H_ */
