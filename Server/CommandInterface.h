/*
 * CommandInterface.h
 *
 *  Created on: Jun 22, 2012
 *      Author: jmonk
 */

#ifndef COMMANDINTERFACE_H_
#define COMMANDINTERFACE_H_

#include "Runnable.h"

namespace dvs {

class CommandInterface;

extern CommandInterface* instance;

class CommandInterface: public Runnable {
public:
	static void setPrompt(char* prompt) {
		instance->setPromptI(prompt);
	}

	CommandInterface(const char* prompt);
	virtual ~CommandInterface();

	void run();

	void commandHandle(char* line);

	void setPromptI(char* prompt);
};

} /* namespace dvs */
#endif /* COMMANDINTERFACE_H_ */
