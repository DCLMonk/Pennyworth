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
#include <sys/select.h>

#include "Runnable.h"

namespace dvs {

extern vector<Room*> rooms;

class Server {
public:
	static Room* getRoom(unsigned int id) {
		while (rooms.size() <= id) {
			rooms.push_back(new Room());
		}
		return rooms[id];
	}

	Server();
	virtual ~Server();

	void addListener(int fd, Runnable* readListener);
	void remListener(int fd);

	void run();

private:
	vector<int> fds;
	vector<Runnable*> readListeners;
	fd_set fdSet;
};

} /* namespace dvs */

extern dvs::Server server;

#endif /* SERVER_H_ */
