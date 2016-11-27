//
//  BOFileUtil_iOS.cpp
//  vsopencvios
//
//  Created by Virendra Shakya on 11/27/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "BOFileUtil_iOS.hpp"

void BOFileUtil_iOS::init() {
	cameraDirectory_ = getWritablePath();
}

string BOFileUtil_iOS::getWritablePath() const {
		// save to document folder
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	std::string strRet = [documentsDirectory UTF8String];
	strRet.append("/");
	return strRet;
}
