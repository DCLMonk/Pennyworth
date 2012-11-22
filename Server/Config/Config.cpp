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
}

Config::~Config() {

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

bool Config::getBool(string skey) {
	return getBool(skey, false);
}

bool Config::getBool(string skey, bool def) {
	if (data.find(skey) == data.end()) {
		data[skey] = def?"true":"false";
	}
	return Util::toBool(data[skey].c_str());
}

void Config::saveConfig() {
	ofstream output(fileName.c_str());

	output << "# Config file: " << fileName << endl;
	output << "#" << endl;
	output << "# This file contains part of the config for a " << endl;
	output << "# Pennyworth Server v" << Server::getVersion() << endl << endl;
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
		input.getline(line, 256);
		if (line[0] != '#') {
			for (int i = 0; (i < 256) && (line != '\0'); i++) {
				if (line[i] == '=') {
					line[i] = '\0';
					string skey(line);
					string val(line + i + 1);
					data[skey] = val;
				}
			}
		}
	}
	input.close();
}

}
