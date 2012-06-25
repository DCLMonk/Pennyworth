/*
 * CommandInterface.cpp
 *
 *  Created on: Jun 22, 2012
 *      Author: jmonk
 */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string>
#include <utility>

#include "CommandInterface.h"
#include "Server.h"
#include "Device/Device.h"
#include "Util.h"
#include "Comm/Communicator.h"
#include "Packets/StartPacket.h"

using namespace std;


namespace dvs {

typedef void(*funcListener)(vector<string>* args);

void listDevices(vector<string>* args);
void quitFunc(vector<string>* args);
void selFunc(vector<string>* args);
void rcommFunc(vector<string>* args);
void listFields(vector<string>* args);

#define NFUNCS 5

pair<string*, funcListener> *(functions[NFUNCS]) = {
	new pair<string*, funcListener>(new string("list"), listDevices),
	new pair<string*, funcListener>(new string("quit"), quitFunc),
	new pair<string*, funcListener>(new string("exit"), quitFunc),
	new pair<string*, funcListener>(new string("select"), selFunc),
	new pair<string*, funcListener>(new string("rcomm"), rcommFunc),
	new pair<string*, funcListener>(new string("fields"), listFields)
};

CommandInterface* instance;

void commandHandleGlobal(char* line) {
	instance->commandHandle(line);
}

CommandInterface::CommandInterface(char* prompt) {
	instance = this;
	rl_callback_handler_install(prompt, (rl_vcpfunc_t*) commandHandleGlobal);
	server.addListener(0, this);
}

CommandInterface::~CommandInterface() {
	rl_callback_handler_remove();
}

void CommandInterface::run() {
	rl_callback_read_char();
}

void CommandInterface::commandHandle(char* line) {
	string l(line);
	if (l.size() > 0) {
		vector<string>* args = Util::split(l, ' ');
		int i;
		for (i = 0; i < NFUNCS; i++) {
			if (*(functions[i]->first) == (*args)[0]) {
				functions[i]->second(args);
				break;
			}
		}
		delete args;
		if (i == NFUNCS) {
			printf("Command: %s\n", line);
		}
		add_history(line);
	}
}

void CommandInterface::setPromptI(char* prompt) {
	rl_set_prompt(prompt);
}

void listDevices(vector<string>* args) {
	printf("Devices: \n");

	for (unsigned int i = 1; i < maxDeviceId; i++) {
		if (Device::getDevice(i) != NULL) {
			printf("\t%d\t%s\t\t%s\n", i, Device::getDevice(i)->getCName().c_str(), Device::getDevice(i)->getName().c_str());
		}
	}
}

void quitFunc(vector<string>* args) {
	exit(0);
}

char buf[10];
unsigned int selected = -1;

void selFunc(vector<string>* args) {
	if (args->size() > 1) {
		selected = atoi((*args)[1].c_str());
	}
	sprintf(buf, "D(%d)->", selected);
	CommandInterface::setPrompt(buf);
}

void rcommFunc(vector<string>* args) {
	Device* device = Device::getDevice(selected);
	if (device != NULL) {
		Communicator* comm = device->getComm();
		StartPacket start;
		comm->sendPacket(&start);
	}
}

void listFields(vector<string>* args) {
	Device* device = Device::getDevice(selected);
	if (device != NULL) {
		printf("Fields:\n");
		for (unsigned int i = 0; i < device->getMaxField(); i++) {
			if (device->hasField(i)) {
				Field* field = device->getField(i);
				printf("\t%s\n", field->getName().c_str());
			}
		}
	}
}

} /* namespace dvs */
