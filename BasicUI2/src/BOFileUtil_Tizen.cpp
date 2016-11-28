/*
 * BOFileUtil_Tizen.cpp
 *
 *  Created on: Nov 27, 2016
 *      Author: virendrashakya
 */


#include <string>
#include <storage.h>
#include <app_common.h>
#include "BOFileUtil_Tizen.h"

using namespace std;

void BOFileUtil_Tizen::init() {
	cameraDirectory_ = getWritablePath();
	//cameraDirectory_ = s.c_str();
}

string BOFileUtil_Tizen::getWritablePath() const {
	std::string strRet = app_get_data_path();
	//strRet.append("/");
	return strRet;
}

