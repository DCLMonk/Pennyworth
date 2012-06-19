#include <stdio.h>
#include <string.h>
#include "Comm/SocketCreator.h"
#include <set>

using namespace std;
using namespace dvs;

int main(int argc, char * argv[]) {
	printf("Test\n");
	printf("More Test\n");
	SocketCreator s(5011);
	set<Communicator*> comms;

	while (true) {
		SocketComm* comm = s.checkConnections();
		if (comm != NULL) {
			comms.insert(comm);
		}
		for (set<Communicator*>::iterator start = comms.begin(); start != comms.end(); start++) {
			Packet::setCurrentComm(*start);
			(*start)->getPacket();
		}
	}
	return 0;
}
