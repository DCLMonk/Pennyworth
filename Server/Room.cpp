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
 * Room.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: jmonk
 */

#include "Room.h"

using namespace std;

namespace dvs {

Room::Room(int id, Config* config) {
	this->id = id;
    this->config = config;
    xl = config->getFloat("x_length", 1);
    yl = config->getFloat("y_length", 1);
    name = config->getString("name", "Room");
}

Room::~Room() {
    delete config;
}

void Room::setXL(float xl) {
    this->xl = xl;
    config->setFloat("x_length", xl);
}

float Room::getXL() {
    return xl;
}

void Room::setYL(float yl) {
    this->yl = yl;
    config->setFloat("y_length", yl);
}

float Room::getYL() {
    return yl;
}

std::string Room::getName() {
    return name;
}

void Room::setName(std::string name) {
    this->name = name;
    config->setString("name", name);
}

void Room::addDevice(Device* device) {
	devices.insert(device);
}

void Room::remDevice(Device* device) {
	devices.erase(device);
}

int Room::getId() {
	return id;
}

} /* namespace dvs */
