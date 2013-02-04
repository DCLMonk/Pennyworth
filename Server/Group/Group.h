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
#ifndef __GROUP_H__
#define __GROUP_H__

#include "Config.h"
#include <string>
#include <vector>

namespace dvs {

// Quick fix for some circular problem
// needs to be fixed
class Device;

class Group {
public:
    Group(std::string name, Config* config);

    ~Group();

    std::vector<Device*> getDevices();

    void addDevice(std::string);
    void remDevice(std::string);

private:
    Config* config;
    string name;
    std::vector<std::string> devices;

};

}

#endif //__GROUP_H__
