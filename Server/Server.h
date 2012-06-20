/*
 * Server.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "Room.h"
#include <vector>
using namespace std;
#include <stdio.h>

namespace dvs {
extern vector<Room*> rooms;

class Server {
public:
	static Room* getRoom(unsigned int id) {
		while (rooms.size() <= id) {
			printf("Adding %d %d\n", rooms.size(), id);
			rooms.push_back(new Room());
		}
		return rooms[id];
	}

	Server();
	virtual ~Server();
};

} /* namespace dvs */
#endif /* SERVER_H_ */
