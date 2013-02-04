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
#include "Group.h"
#include "Device.h"
#include "Util.h"

namespace dvs {

Group::Group(std::string name, Config* config) {
    this->config = config;
    string s = config->getString("DEVS", "");
    if (s.size() > 0) {
        vector<string>* d = Util::split(s, ',');
        devices = *d;
        delete d;
    }
    config->setString("name", name);
}

Group::~Group() {
    delete config;
}

void Group::addDevice(std::string dev) {
    devices.push_back(dev);
    config->setString("DEVS", Util::concat(&devices, ','));
}

void Group::remDevice(std::string dev) {
    devices.erase(std::remove(devices.begin(), devices.end(), dev), devices.end());
    config->setString("DEVS", Util::concat(&devices, ','));
}

std::vector<Device*> Group::getDevices() {
    vector<Device*> devs;

    for (unsigned int i = 0; i < devices.size(); i++) {
        Device* d = Device::getDevice(devices[i]);
        if (d != NULL) {
            devs.push_back(d);
        }
    }

    return devs;
}

}
