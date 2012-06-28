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
