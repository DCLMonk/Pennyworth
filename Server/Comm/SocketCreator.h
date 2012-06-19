/*
 * SocketCreator.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef SOCKETCREATOR_H_
#define SOCKETCREATOR_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "SocketComm.h"

namespace dvs {

class SocketCreator {
public:
	SocketCreator(int port);
	~SocketCreator();

	SocketComm* checkConnections();

private:
	int sockfd;
	struct sockaddr_in cli_addr;
	socklen_t clilen;

};

}

#endif /* SOCKETCREATOR_H_ */
