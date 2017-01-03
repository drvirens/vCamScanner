/*
 * TizenUtils.h
 *
 *  Created on: Mar 15, 2012
 *      Author: vshakya
 */

#ifndef __TIZEN__UTILS_H_
#define __TIZEN__UTILS_H_

#include <stdio.h>
#include <locale.h>
#include <string>
#include <FBase.h>

using namespace Tizen::Base;
using namespace std;

class Utils {
public:
	static std::string* GetCString(const Tizen::Base::String& sBadaStr);
	static int GetRandomNumber();
	static char* my_itoa(int value, char* result, int base);
	static const char* GenerateStrName(const char* aStr, int aRandomNum);
};

#endif /* __TIZEN__UTILS_H_ */
