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
 * Config.h
 *
 *  Created on: Nov 21, 2012
 *      Author: jmonk
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <map>

using namespace std;

namespace dvs {

class Config {
public:
	Config(std::string fileName);
    Config(const Config& orig);
	virtual ~Config();

	string getString(string skey);
	string getString(string skey, string def);
	void setString(string skey, string def);

	int getInt(string skey);
	int getInt(string skey, int def);
	void setInt(string skey, int def);

	float getFloat(string skey);
	float getFloat(string skey, float def);
	void setFloat(string skey, float def);

	bool getBool(string skey);
	bool getBool(string skey, bool def);
	void setBool(string skey, bool def);

	void saveConfig();

private:
	void loadConfig();

	std::map<std::string, std::string> data;
	std::string fileName;
};

}

#endif /* CONFIG_H_ */
