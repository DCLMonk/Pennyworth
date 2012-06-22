/*
 * Util.h
 *
 *  Created on: Jun 22, 2012
 *      Author: jmonk
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

namespace dvs {

class Util {
public:
	static vector<string>* split(string s, char tok) {
		vector<string>* ret = new vector<string>;
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, tok)) {
			ret->push_back(item);
		}
		return ret;
	}
};

} /* namespace dvs */
#endif /* UTIL_H_ */
