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
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <getopt.h>
#include <string.h>

#include <set>
#include <iostream>

#include "CommandInterface.h"
#include "Server.h"
#include "SocketCreator.h"
#include "CSocketCreator.h"
#include "SerialComm.h"
#include "SocketComm.h"
#include "Runnable.h"
#include "DeviceEvent.h"

using namespace std;
using namespace dvs;

class DeviceHandler : public Runnable {
    void run() {
        DeviceEvent* event = (DeviceEvent*)EventManager::getCurrentEvent();
        cout << "Device Connected: " << event->getDevice()->getName() << endl;
    }
};

class CreateHandler: public Runnable {
public:

	CreateHandler(SocketCreator* creator) {
		this->creator = creator;
	}

	void run() {
		creator->checkConnections();
//		if (comm != NULL) {
//			comms.insert(comm);
//		}
	}
private:
	SocketCreator* creator;
};

class CCreateHandler: public Runnable {
public:

	CCreateHandler(CSocketCreator* creator) {
		this->creator = creator;
	}

	void run() {
		creator->checkConnections();
//		if (comm != NULL) {
//			comms.insert(comm);
//		}
	}
private:
	CSocketCreator* creator;
};

#define DEFAULT_PORT 5010
#define DEFAULT_USER_PORT 8010

const char* optString = "p:d:u:c:h";

static const struct option longOpts[] = {
	{ "device", required_argument, NULL, 'd' },
	{ "port", required_argument, NULL, 'p' },
	{ "uport", required_argument, NULL, 'u' },
	{ "configdir", required_argument, NULL, 'c' },
	{ "help", optional_argument, NULL, 'h' },

};

int main(int argc, char * argv[]) {
	SocketCreator* s = NULL;
	CSocketCreator* cs = NULL;
    char baseLocBuffer[256];

    sprintf(baseLocBuffer, "%s/.Pennyworth", getenv("HOME"));
    char* cconfigLoc = baseLocBuffer;

	signal(SIGPIPE, SIG_IGN);

	int longIndex;
	int opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	while (opt != -1) {
		switch (opt) {
		case 'h':
			printf("Usage: %s [OPTION]\n", argv[0]);
			return 0;
		case 'd':
			printf("Connecting to %s\n", optarg);
			new SerialComm(optarg);
			break;
		case 'p':
			printf("Port: %d\n", atoi(optarg));
			s = new SocketCreator(atoi(optarg));
			break;
		case 'u':
			printf("User Port: %d\n", atoi(optarg));
			cs = new CSocketCreator(atoi(optarg));
			break;
		case 'c':
            cconfigLoc = optarg;
			break;
		default:
			/* You won't actually get here. */
			break;
		}

		opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	}
    std::string configLoc(cconfigLoc);
    Server server(configLoc);
	if (s == NULL) {
		printf("Port: %d\n", DEFAULT_PORT);
		s = new SocketCreator(DEFAULT_PORT);
	}
	if (cs == NULL) {
		printf("User Port: %d\n", DEFAULT_USER_PORT);
		cs = new CSocketCreator(DEFAULT_USER_PORT);
	}
	CommandInterface command("NONE->");

	server.addListener(s->getFd(), new CreateHandler(s));
	server.addListener(cs->getFd(), new CCreateHandler(cs));

	server.run();

	delete s;
//	while (true) {
//		for (set<Communicator*>::iterator start = comms.begin(); start != comms.end(); start++) {
//			Packet::setCurrentComm(*start);
//			(*start)->getPacket();
//		}
//	}
	return 0;
}
