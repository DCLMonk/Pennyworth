#include <stdio.h>
#include <string.h>
#include "Comm/SocketCreator.h"
#include "Comm/SerialComm.h"
#include "Comm/SocketComm.h"
#include <set>
#include <sys/time.h>

using namespace std;
using namespace dvs;

int main(int argc, char * argv[]) {
	printf("Test\n");
	printf("More Test\n");
	SocketCreator s(5010);
	set<Communicator*> comms;
    struct timeval t;
    double time1, time2;

    gettimeofday(&t, NULL);
    time1 = t.tv_sec + (t.tv_usec / 1000000.0);

	if (argc > 1) {
		comms.insert(new SerialComm(argv[1]));
	}

	while (true) {
		SocketComm* comm = s.checkConnections();
		if (comm != NULL) {
			comms.insert(comm);
		}
		for (set<Communicator*>::iterator start = comms.begin(); start != comms.end(); start++) {
			Packet::setCurrentComm(*start);
			(*start)->getPacket();
		}

	    gettimeofday(&t, NULL);
	    time2 = t.tv_sec + (t.tv_usec / 1000000.0);
	    if (time2 - time1 > 1) {
	    	printf("Sending...\n");
	    	for (int id = 1; id < maxDeviceId; id++) {
	    		Device* device = Device::getDevice(id);
	    		for (int i = 0; i < device->getNFields(); i++) {
	    			SetFieldPacket packet(device, i);
	    			packet.send();
	    		}
	    	}
	    	time1 = time2;
	    }
	}
	return 0;
}
