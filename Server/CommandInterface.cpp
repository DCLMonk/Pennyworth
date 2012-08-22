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
#include "Communicator.h"
#include "StartPacket.h"
#include "Field.h"

using namespace std;


namespace dvs {

typedef void(*funcListener)(vector<string>* args);

void listDevices(vector<string>* args);
void quitFunc(vector<string>* args);
void selFunc(vector<string>* args);
void rcommFunc(vector<string>* args);
void listFields(vector<string>* args);
void setField(vector<string>* args);
void printField(vector<string>* args);
void printDevice(vector<string>* args);

#define NFUNCS 9

pair<string*, funcListener> *(functions[NFUNCS]) = {
	new pair<string*, funcListener>(new string("list"), listDevices),
	new pair<string*, funcListener>(new string("quit"), quitFunc),
	new pair<string*, funcListener>(new string("exit"), quitFunc),
	new pair<string*, funcListener>(new string("select"), selFunc),
	new pair<string*, funcListener>(new string("rcomm"), rcommFunc),
	new pair<string*, funcListener>(new string("fields"), listFields),
	new pair<string*, funcListener>(new string("set"), setField),
	new pair<string*, funcListener>(new string("print"), printField),
	new pair<string*, funcListener>(new string("printd"), printDevice)
};

CommandInterface* instance;
char* print_buffer;
int print_index;
int buffer_length;

#include <stdarg.h>

void copy_to_buffer(char* string, int length) {
	for (int i = 0; (i < length) && (print_index < buffer_length - 1); i++) {
		print_buffer[print_index++] = string[i];
	}
	print_buffer[print_index++] = '\0';
}

int print(const char* format, ...) {
	char buffer[512];
	int ret = 0;
	va_list args;
	va_start(args, format);

	if (print_buffer != NULL) {
		ret = vsprintf(buffer, format, args);
		copy_to_buffer(buffer, ret);
	} else {
		ret = vprintf(format, args);
	}

	return ret;
}

void commandHandleGlobal(char* line) {
	instance->commandHandle(line);
}

CommandInterface::CommandInterface(const char* prompt) {
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

void CommandInterface::commandHandle(char* line, char* output, int out_len) {
	print_buffer = output;
	print_index = 0;
	buffer_length = out_len;

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
			print("Invalid Command: %s %d\n", line, strlen(line));
			for (int i = 0; i < strlen(line); i++) {
				printf("%c-", line[i]);
			}
		}
	}
	print_buffer = NULL;
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
			print("Invalid Command: %s\n", line);
		}
		add_history(line);
	}
}

void CommandInterface::setPromptI(char* prompt) {
	rl_set_prompt(prompt);
}

unsigned int selected = -1;

void listDevices(vector<string>* args) {
	print("Devices: \n");

	for (unsigned int i = 1; i < maxDeviceId; i++) {
		if (Device::getDevice(i) != NULL) {
			if (i == selected) {
				print("-->\t%d\t%s\t\t%s\n", i, Device::getDevice(i)->getCName().c_str(), Device::getDevice(i)->getName().c_str());
			} else {
				print("\t%d\t%s\t\t%s\n", i, Device::getDevice(i)->getCName().c_str(), Device::getDevice(i)->getName().c_str());
			}
		}
	}
}

void quitFunc(vector<string>* args) {
	exit(0);
}

char buf[10];

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
	} else {
		print("Error: No Device Selected\n");
	}
}

void listFields(vector<string>* args) {
	Device* device = Device::getDevice(selected);
	if (device != NULL) {
		print("Fields:\n");
		for (unsigned int i = 0; i < device->getMaxField(); i++) {
			if (device->hasField(i)) {
				Field* field = device->getField(i);
				print("\t%d\t%s\t%s\n", i, field->getName().c_str(), typeStrings[(int)field->getType()].c_str());
			}
		}
	} else {
		print("Error: No Device Selected\n");
	}
}

void setField(vector<string>* args) {
	Device* device = Device::getDevice(selected);
	if (device != NULL) {
		if (args->size() > 2) {
			Field* field = device->getField(atoi((*args)[1].c_str()));
			if (field != NULL) {
				if (field->isWritable()) {
					field->setRealString((*args)[2]);
				} else {
					print("Error: Field is Read-only\n");
				}
			} else {
				print("Error: Invalid Field %d\n", atoi((*args)[1].c_str()));
			}
		} else {
			print("Usage: set <field id> <value>\n");
		}
	} else {
		print("Error: No Device Selected\n");
	}
}

void printDevice(vector<string>* args) {
	Device* device = Device::getDevice(selected);
	if (device == NULL) {
		if (args->size() > 1) {
			device = Device::getDevice(atoi((*args)[1].c_str()));
		}
		if (device == NULL) {
			print("Error: No Device Selected\n");
			return;
		}
	}
	print("Device ID: %d\n", device->getId());
	print("Device: %s\t\tCommon Name: %s\n", device->getName().c_str(), device->getCName().c_str());
	print("Room: %d\t X: %lf\tY: %lf\n", device->getRoom()->getId(), device->getX(), device->getY());
}

void printField(vector<string>* args) {
	Device* device = Device::getDevice(selected);
	if (device != NULL) {
		if (args->size() > 1) {
			Field* field = device->getField(atoi((*args)[1].c_str()));

			if (field != NULL) {
				print("Field: %d - %s:\t%s\n", field->getId(), typeStrings[(int)field->getType()].c_str(), field->getName().c_str());
				print("%s\t", field->isWritable()?"Writable":"Read-Only");
				if (field->isVolatile()) {
					print("Volatile\t");
				}
				print("\n");
				switch (field->getType()) {
				case BOOL:
					print("Value: %s\n", ((BooleanField*)field)->getBool()?"True":"False");
					break;
				case INTEGER:
					print("Value: %d\n", ((IntegerField*)field)->getInt());
					break;
				case FLOAT:
					print("Value: %lf\n", ((FloatField*)field)->getFloat());
					break;
				case FIXED:
					print("Value: %lf\n", ((FixedField*)field)->getFloat());
					print("One Reference: %d\n", ((FixedField*)field)->getOne());
					break;
				case STRING:
					print("Value: %s\n", ((StringField*)field)->getValue().c_str());
					break;
				}
			} else {
				print("Error: Invalid Field %d\n", atoi((*args)[1].c_str()));
			}
		} else {
			print("Usage: print <field id>\n");
		}
	} else {
		print("Error: No Device Selected\n");
	}
}

} /* namespace dvs */
