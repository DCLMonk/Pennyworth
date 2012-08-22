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
	Room(int id);
	virtual ~Room();

	void addDevice(Device* device);

	void remDevice(Device* device);

	int getId();
private:
	std::set<Device*> devices;
	int id;
};

} /* namespace dvs */
#endif /* ROOM_H_ */
