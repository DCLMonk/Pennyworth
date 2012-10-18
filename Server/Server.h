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
 * Server.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "Room.h"
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;
#include <stdio.h>
#include <sys/select.h>

#include "Runnable.h"
#include "User.h"

namespace dvs {

extern unsigned int maxUserId;
extern queue<unsigned int> availableIds;
extern map<unsigned int, User*> users;
extern vector<Room*> rooms;

class Server {
public:
	static bool isValid(string user, string pass) {
		return true;
	}

	static unsigned int allocateUID() {
		if (availableIds.size()) {
			int id = availableIds.front();
			availableIds.pop();
			return id;
		}
		return maxUserId++;
	}

	static void freeUID(unsigned int id) {
		availableIds.push(id);
		users[id] = NULL;
	}

	static User* getUser(unsigned int id) {
		return users[id];
	}

	static User* newUser(CCommunicator* comm) {
		return new User(comm);
	}

	static void setUser(unsigned int id, User* user) {
		users[id] = user;
	}

	static Room* getRoom(unsigned int id) {
		while (rooms.size() <= id) {
			rooms.push_back(new Room(rooms.size()));
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
