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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

namespace dvs {

SerialComm::SerialComm(char* device) {
    struct termios tc;                // terminal control structure

    //todo serial port should not be hard coded
    fd = open(device, O_RDWR|O_NOCTTY);  // really ought to check for error
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
}

SerialComm::~SerialComm() {
	close(fd);
}

void SerialComm::sendPacket(Packet* packet) {
	write(fd, packet->getData(), packet->getLength());
	printf("Send %d\n", packet->getLength());
}

Packet* SerialComm::getPacket() {
	if (index == 0) {
		int rd = read(fd, buffer, 1);
		if (rd > 0) {
			printf("Start: %d\n", buffer[0]);
			size = buffer[0];
			index = 1;
		}
	} else {
		int rd = read(fd, buffer + index, 1 + size - index);
		if (rd > 0) {
			printf("Read: %d\n", rd);
			index += rd;
			if (index == size + 1) {
				makePacket();
				index = 0;
			}
		}
	}
	return NULL;
}

} /* namespace dvs */
