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
	Start=0,
	Init,
	Init_Common_Name,
	Init_Location,
	Init_Field,
	Get_Field,
	Field_Value,
	Set_Field,
	Subscribe,
	Set_One
};

} /* namespace DVS */

#endif /* PACKET_H_ */
