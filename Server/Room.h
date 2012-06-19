/*
 * Room.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <set>
using namespace std;

namespace dvs {

class Device;

class Room {
public:
	Room();
	virtual ~Room();

	void addDevice(Device* device);

	void remDevice(Device* device);
private:
	set<Device*> devices;
};

} /* namespace dvs */
#endif /* ROOM_H_ */
