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
 * Main.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: jmonk
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <getopt.h>
#include <string.h>
#include <termios.h>

#include <sys/select.h>

#include <vector>

#include "CSocketComm.h"
#include "LoginPacket.h"
#include "GetDevicesPacket.h"
#include "GetFieldsPacket.h"

#define error perror

#define DEFAULT_PORT 8010

using namespace std;
using namespace dvs;

enum {
	DEVICE=1,
	FIELD
};

int mode = DEVICE;
int fd;
vector<Device*> devices;
vector<Field*> fields;

void sendSerial(string str) {
	write(fd, str.c_str(), strlen(str.c_str()));
	write(fd, "\r", 1);
	fsync(fd);
}

void sendDevice(Device* device) {
	string name = device->getCName();
	devices.push_back(device);
	sendSerial(name);
	printf("Sending Device: %s\n", name.c_str());
}

void sendField(Field* field) {
	string name = field->getName();
	fields.push_back(field);
	sendSerial(name);
	printf("Sending Field: %s\n", name.c_str());
}

bool getDevices(CPacket* packet, void* data) {
	CSocketComm* comm = (CSocketComm*)data;
	GetDevicesPacket p(comm);
	p.send();
	return true;
}

bool gotDevice(CPacket* packet, void* data) {
	CSocketComm* comm = (CSocketComm*)data;
	Device* device = ((DeviceDefPacket*)packet)->getDevice();
	GetFieldsPacket p(device->getId(), comm);
	p.send();
	if (mode == DEVICE) {
		sendDevice(device);
	}
	return false;
}
bool gotField(CPacket* packet, void* data) {
	Field* field = ((FieldInfoPacket*)packet)->getField();
	if (mode == FIELD) {
		sendField(field);
	}
	return false;
}

int main(int argc, char* argv[]) {
	struct termios tc; // terminal control structure
	int portno;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	fd_set fdSet;
	int max;
	const char* serial = "/dev/ttyUSB0";
	char serialBuffer[64];
	unsigned int serialIndex;

	portno = DEFAULT_PORT;

//	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
//	if (sockfd < 0)
//		error("ERROR opening socket");
//	server = gethostbyname("localhost");
//	if (server == NULL) {
//		fprintf(stderr, "ERROR, no such host\n");
//		exit(0);
//	}
//	bzero((char *) &serv_addr, sizeof(serv_addr));
//	serv_addr.sin_family = AF_INET;
//	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
//			server->h_length);
//	serv_addr.sin_port = htons(portno);
//	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
//		error("ERROR connecting");

	fd = open(serial, O_RDWR | O_NOCTTY); // really ought to check for error
	tcgetattr(fd, &tc);
//	cfmakeraw(&tc);
    tc.c_iflag = IGNPAR;
    tc.c_oflag = 0;
    tc.c_cflag = CS8 | CREAD | CLOCAL; //8 bit chars enable receiver no modem status lines
    tc.c_lflag = 0;

	//todo baud rate should not be hard coded
	cfsetispeed(&tc, B9600);
	cfsetospeed(&tc, B9600);
	//todo should have bits per character set
	tcsetattr(fd, TCSANOW, &tc);
	fcntl(fd, F_SETFL, O_NONBLOCK);

//	CSocketComm socketComm(sockfd);
//	socketComm.registerListener(UID, &socketComm, getDevices);
//	socketComm.registerListener(DEVICE_DEF, &socketComm, gotDevice);
//	socketComm.registerListener(FIELD_INFO, &socketComm, gotField);
//	LoginPacket loginPacket("Me", "MyPass", &socketComm);
//	loginPacket.send();
	sendSerial("Test String");
	sendSerial("Test String");
	sendSerial("Test String");

	while (true) {
//		FD_ZERO(&fdSet);
//		FD_SET(sockfd, &fdSet);
//		FD_SET(fd, &fdSet);
//		max = sockfd + 1;
//		if (fd > sockfd) max = fd + 1;
//		int ret = select(max, &fdSet, NULL, NULL, NULL);

//		if (ret > 0) {
//			if (FD_ISSET(sockfd, &fdSet)) {
//				socketComm.getPacket();
//			}
//			if (FD_ISSET(fd, &fdSet)) {
				int ret = read(fd, serialBuffer + serialIndex, 64 - serialIndex);
				if (ret > 0) {
					printf("Read %d\n", ret);
					serialIndex += ret;
					for (unsigned int i = 0; i < serialIndex; i++) {
						if (serialBuffer[i] == '\n') {
							serialBuffer[i] = '\0';
							unsigned int id = atoi(serialBuffer + 1);
							if (serialBuffer[0] == 'D') {
								Device* device = devices[id];
								sendSerial(":2");

								for (unsigned int i = 0; i < device->getMaxField(); i++) {
									if (device->hasField(i)) {
										sendField(device->getField(i));
									}
								}
								sendSerial("Done");
							} else {
								if (id < fields.size()) {
									fields[id]->increment();
								} else {
									devices.clear();
									sendSerial(":1");
									for (unsigned int fid = 0; fid < maxDeviceId + 1; fid++) {
										Device* device = Device::getDevice(fid);
										if (device != NULL) {
											sendDevice(device);
										}
									}
								}
							}
							for (unsigned int j = i+1; j < serialIndex; j++) {
								serialBuffer[j-(i+1)] = serialBuffer[j];
							}
							serialIndex -= i + 1;
							i = 0;
						}
					}
				}
//			}
//		} else {
//			printf("Hmm %d\n", ret);
//		}
	}

	return 0;
}



