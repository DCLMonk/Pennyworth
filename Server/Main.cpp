#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <getopt.h>
#include <string.h>

#include <set>

#include "CommandInterface.h"
#include "Server.h"
#include "Comm/SocketCreator.h"
#include "Comm/SerialComm.h"
#include "Comm/SocketComm.h"
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

#define DEFAULT_PORT 5010

char* optString = "p:d:h";

static const struct option longOpts[] = {
	{ "device", required_argument, NULL, 'd' },
	{ "port", required_argument, NULL, 'p' },

};

int main(int argc, char * argv[]) {
	SocketCreator* s = NULL;

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
	CommandInterface command("NONE->");

	server.addListener(s->getFd(), new CreateHandler(s));

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
