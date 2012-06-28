/*
 * CSocketCreator.h
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#ifndef CSOCKETCREATOR_H_
#define CSOCKETCREATOR_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "CSocketComm.h"

namespace dvs {

class CSocketCreator {
public:
	CSocketCreator(int port);
	~CSocketCreator();

	CSocketComm* checkConnections();

	int getFd();

private:
	int sockfd;
	struct sockaddr_in cli_addr;
	socklen_t clilen;

};

}

#endif /* CSOCKETCREATOR_H_ */
