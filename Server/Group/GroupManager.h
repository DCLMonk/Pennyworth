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
#ifndef __GROUPMANAGER_H__
#define __GROUPMANAGER_H__

#include "Group.h"
#include "ConfigManager.h"
#include <string>

namespace dvs {

class GroupManager {
public:

    GroupManager();

    void readConfigs();

    Group* getGroup(std::string name);

protected:

private:
    ConfigManager* groupConfigs;
    std::map<std::string, Group*> groups; 

};

}

#endif //__GROUPMANAGER_H__
