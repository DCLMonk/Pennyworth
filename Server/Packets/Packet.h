/*
 * Packet.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef PACKET_H_
#define PACKET_H_

#include "../Device/Device.h"
namespace dvs {

class Communicator;

extern Communicator* currentCommunicator;

class Packet {
public:
	static Communicator* getCurrentComm() {
		return currentCommunicator;
	}

	static void setCurrentComm(Communicator* comm) {
		currentCommunicator = comm;
	}

	Packet(unsigned char *data);
	Packet(unsigned int length, unsigned int device, unsigned char pid);

	virtual ~Packet();

	Device *getDevice();

	void send();

	unsigned char *getData();

	unsigned int getLength();

	unsigned char getType();
protected:
	unsigned char* data;
	unsigned char pid;
	unsigned int length;
	unsigned int device;
	bool allocated;
private:

};

enum PacketType {
	Start = 0,
	Init = 1,
	Init_Common_Name = 2,
	Init_Location = 3,
	Init_Field = 4,
	Get_Field = 5,
	Field_Value = 6,
	Set_Field = 7,
	Subscribe = 8,
	Set_One = 9
};

} /* namespace DVS */

#include "StartPacket.h"
#include "InitPacket.h"
#include "InitCNamePacket.h"
#include "InitLocationPacket.h"
#include "InitFieldPacket.h"
#include "GetFieldPacket.h"
#include "FieldValuePacket.h"
#include "SetFieldPacket.h"
#include "SubscribePacket.h"
#include "SetOnePacket.h"

#endif /* PACKET_H_ */
