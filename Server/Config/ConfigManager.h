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
 * ConfigManager.h
 *
 *  Created on: Nov 21, 2012
 *      Author: jmonk
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include <string>
#include "Config.h"
#include <vector>

namespace dvs {

class ConfigManager {
public:
	ConfigManager(std::string baseFolder);
	virtual ~ConfigManager();

    /**
     * Get a manager for a subfolder in the config.
     *
     * This gets a config manager to manage a subfolder of
     * the current manager.  Presumably the subfolder will
     * contain configs to be read.
     *
     * Alloc Notice: The return value of this function is
     * allocated using new and should be de-alloced using
     * delete when the caller is done with it.
     *
     * @param subFolder The child folder to be opened
     */
	ConfigManager* getSubConfig(std::string subFolder);

	Config getConfig(std::string configName);
    vector<Config> getAllConfigs();

private:
	std::string baseFolder;
};

}

#endif /* CONFIGMANAGER_H_ */
