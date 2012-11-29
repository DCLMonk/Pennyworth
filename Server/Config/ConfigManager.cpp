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
 * ConfigManager.cpp
 *
 *  Created on: Nov 21, 2012
 *      Author: jmonk
 */

#include "ConfigManager.h"
#include <errno.h>
#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;

namespace dvs {

ConfigManager::ConfigManager(string baseFolder) {
	this->baseFolder = baseFolder;
    mkdir(baseFolder.c_str(), 0755);
}

ConfigManager::~ConfigManager() {

}

ConfigManager* ConfigManager::getSubConfig(string subFolder) {
	string newFolder = baseFolder;
	newFolder.append("/").append(subFolder);
	return new ConfigManager(newFolder);
}

Config ConfigManager::getConfig(string configName) {
	string newFolder = baseFolder;
	newFolder.append("/").append(configName);
	Config ret = Config(newFolder);
    return ret;
}

vector<Config> ConfigManager::getAllConfigs() {
    vector<Config> ret;

    DIR *dp;
    struct dirent *dirp;
    if((dp = opendir(baseFolder.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << baseFolder << endl;
        return ret;
    }

    while ((dirp = readdir(dp)) != NULL) {
        ret.push_back(getConfig(string(dirp->d_name)));
    }
    closedir(dp);

    return ret;
}

}
