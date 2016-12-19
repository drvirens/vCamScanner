//
//  model_immutable_login.hpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/10/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef model_immutable_login_hpp
#define model_immutable_login_hpp

#include <string>
using namespace std;

class TLoginMessageLayout
	{
public:
	TLoginMessageLayout(const string& aUserName, const string& aPassword, const string& aSecurity);
	TLoginMessageLayout();
	~TLoginMessageLayout();
	const string& userName() const { return iUserName; }
	
public:
	string iUserName;
	string iPassword;
	string iSecurity;
	};

#endif /* model_immutable_login_hpp */
