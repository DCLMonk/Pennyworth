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
	virtual ~Config();

	string getString(string skey);
	string getString(string skey, string def);

	int getInt(string skey);
	int getInt(string skey, int def);

	float getFloat(string skey);
	float getFloat(string skey, float def);

	bool getBool(string skey);
	bool getBool(string skey, bool def);

	void saveConfig();

private:
	void loadConfig();

	std::map<std::string, std::string> data;
	std::string fileName;
};

}

#endif /* CONFIG_H_ */
