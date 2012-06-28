#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <getopt.h>
#include <string.h>

#include <set>

#include "CommandInterface.h"
#include "Server.h"
#include "SocketCreator.h"
#include "CSocketCreator.h"
#include "SerialComm.h"
#include "SocketComm.h"
#include "Runnable.h"

using namespace std;
using namespace dvs;
Server server;

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

const char* optString = "p:d:u:h";

static const struct option longOpts[] = {
	{ "device", required_argument, NULL, 'd' },
	{ "port", required_argument, NULL, 'p' },
	{ "uport", required_argument, NULL, 'u' },

};

int main(int argc, char * argv[]) {
	SocketCreator* s = NULL;
	CSocketCreator* cs = NULL;

	signal(SIGPIPE, SIG_IGN);

	if (argc > 1) {
	}
	int longIndex;
	int opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	while (opt != -1) {
		switch (opt) {
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
		default:
			/* You won't actually get here. */
			break;
		}

		opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
	}
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
