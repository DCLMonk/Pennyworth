/*
 * SerialComm.cpp
 *
 *  Created on: Jun 20, 2012
 *      Author: jmonk
 */

#include "SerialComm.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

namespace dvs {

SerialComm::SerialComm(char* device) {
	struct termios tc; // terminal control structure
	std::string dev(device);
	name = "Serial ";
	name.append(dev);

	fd = open(device, O_RDWR | O_NOCTTY); // really ought to check for error
	tcgetattr(fd, &tc);
	cfmakeraw(&tc);
//    tc.c_iflag = IGNPAR;
//    tc.c_oflag = 0;
//    tc.c_cflag = CS8 | CREAD | CLOCAL; //8 bit chars enable receiver no modem status lines
//    tc.c_lflag =0 ;

	//todo baud rate should not be hard coded
	cfsetispeed(&tc, B9600);
	cfsetospeed(&tc, B9600);
	//todo should have bits per character set
	tcsetattr(fd, TCSANOW, &tc);

	fcntl(fd, F_SETFL, O_NONBLOCK);
	StartPacket p;
	sendPacket(&p);
	server.addListener(fd, new CommHandler(this));
	printf("New Serial Port\n");
}

} /* namespace dvs */
