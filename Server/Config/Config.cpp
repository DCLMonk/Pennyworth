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
 * Config.cpp
 *
 *  Created on: Nov 21, 2012
 *      Author: jmonk
 */

#include "Config.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Server.h"
#include "Util.h"

using namespace std;

namespace dvs {

Config::Config(std::string fileName) {
	this->fileName = fileName;
	loadConfig();
}

Config::Config(const Config& orig) : data(orig.data), fileName(orig.fileName) {
    
}

Config::~Config() {
	saveConfig();
}

string Config::getString(string skey) {
	return getString(skey, "");
}

string Config::getString(string skey, string def) {
	if (data.find(skey) == data.end()) {
		data[skey] = def;
	}
	return data[skey];
}

void Config::setString(string skey, string def) {
	data[skey] = def;
}

int Config::getInt(string skey) {
	return getInt(skey, 0);
}

int Config::getInt(string skey, int def) {
	if (data.find(skey) == data.end()) {
		char buf[20];
		sprintf(buf, "%d", def);
		string val(buf);
		data[skey] = val;
	}
	return atoi(data[skey].c_str());
}

void Config::setInt(string skey, int def) {
    char buf[20];
    sprintf(buf, "%d", def);
    string val(buf);
    data[skey] = val;
}

float Config::getFloat(string skey) {
	return getFloat(skey, 0);
}

float Config::getFloat(string skey, float def) {
	if (data.find(skey) == data.end()) {
		char buf[20];
		sprintf(buf, "%lf", def);
		string val(buf);
		data[skey] = val;
	}
	return atof(data[skey].c_str());
}

void Config::setFloat(string skey, float def) {
    char buf[20];
    sprintf(buf, "%lf", def);
    string val(buf);
    data[skey] = val;
}

bool Config::getBool(string skey) {
	return getBool(skey, false);
}

bool Config::getBool(string skey, bool def) {
	if (data.find(skey) == data.end()) {
		data[skey] = def?"true":"false";
	}
	return Util::toBool(data[skey].c_str());
}

void Config::setBool(string skey, bool def) {
    data[skey] = def?"true":"false";
}

void Config::saveConfig() {
	ofstream output(fileName.c_str());

	output << "# Config file: " << fileName << endl;
	output << "#" << endl;
	output << "# This file contains part of the config for a " << endl;
	output << "# Pennyworth Server v" << Server::getServer()->getVersion() << endl << endl;
	for (map<string, string>::iterator it = data.begin(); it != data.end(); it++) {
		output << (*it).first;
		output << "=";
		output << (*it).second;
		output << endl;
	}
	output << endl;

	output.close();
}

void Config::loadConfig() {
	ifstream input(fileName.c_str());
	char line[256];

	while (input.good()) {
		for (int i = 0; (i < 256); i++) {
			line[i] = '\0';
		}
		input.getline(line, 256);
		if (line[0] != '#') {
			for (int i = 0; (i < 256) && (line != '\0'); i++) {
				if (line[i] == '=') {
					line[i] = '\0';
					string skey(line);
					string val(line + i + 1);
					data[skey] = val;
					break;
				}
			}
		}
	}
	input.close();
}

}
