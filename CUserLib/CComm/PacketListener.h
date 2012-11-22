/*
 * PacketListener.h
 *
 *  Created on: Nov 21, 2012
 *      Author: jmonk
 */

#ifndef PACKETLISTENER_H_
#define PACKETLISTENER_H_

namespace dvs {

class CPacket;

typedef bool(*Listener)(CPacket*, void*);

class PacketListener {
public:
	PacketListener(int packetType, void* data, Listener listener);
	virtual ~PacketListener();

	int packetType;
	Listener listener;
	void* data;
};

} /* namespace dvs */
#endif /* PACKETLISTENER_H_ */
