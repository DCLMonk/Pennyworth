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
#include "GroupManager.h"
#include <sstream>
#include "Server.h"

using namespace std;

namespace dvs {

GroupManager::GroupManager() {
}

GroupManager::~GroupManager() {
    delete groupConfigs;
    for (std::map<string,Group*>::iterator it=groups.begin(); it!=groups.end(); ++it) {
        delete it->second;
    }
}

void GroupManager::readConfigs() {
    groupConfigs = Server::getServer()->getConfigManager().getSubConfig("Groups");
    vector<Config*> configs = groupConfigs->getAllConfigs();
    for (unsigned int i = 0; i < configs.size(); i++) {
        string name = configs[i]->getString("name");
        groups[name] = new Group(name, configs[i]);
    }
}

Group* GroupManager::getGroup(std::string ss) {
    if (groups.find(ss) == groups.end()) {
        string cfg(".cfg");
        groups[ss] = new Group(ss, groupConfigs->getConfig(ss + cfg));
    }
    return groups[ss];
}

}
