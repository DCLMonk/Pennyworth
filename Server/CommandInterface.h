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
	void commandHandle(char* line, char* output, int out_len);

	void setPromptI(char* prompt);
};

} /* namespace dvs */
#endif /* COMMANDINTERFACE_H_ */
