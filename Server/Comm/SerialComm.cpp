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
    Server::getServer()->addListener(fd, new CommHandler(this));
}

} /* namespace dvs */
