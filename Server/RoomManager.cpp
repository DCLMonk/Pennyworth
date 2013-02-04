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
#include "RoomManager.h"
#include <sstream>
#include "Server.h"

namespace dvs {

RoomManager::RoomManager() {
}

RoomManager::~RoomManager() {
    for (unsigned int i = 0; i < rooms.size(); i++) {
        delete rooms[i];
    }
    delete roomConfigs;
}

void RoomManager::readConfigs() {
    roomConfigs = Server::getServer()->getConfigManager().getSubConfig("Rooms");
    vector<Config*> configs = roomConfigs->getAllConfigs();
    for (unsigned int i = 0; i < configs.size(); i++) {
        stringstream ss(stringstream::out);
        ss << rooms.size();
        ss << ".cfg";
        rooms.push_back(new Room(rooms.size(), roomConfigs->getConfig(ss.str())));
    }
}

Room* RoomManager::getRoom(unsigned int id) {
    while (rooms.size() <= id) {
        stringstream ss(stringstream::out);
        ss << rooms.size();
        ss << ".cfg";
        rooms.push_back(new Room(rooms.size(), roomConfigs->getConfig(ss.str())));
    }
    return rooms[id];
}

}
