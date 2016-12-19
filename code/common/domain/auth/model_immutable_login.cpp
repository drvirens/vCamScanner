//
//  model_immutable_login.cpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/10/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "model_immutable_login.hpp"
#include "trace.h"

TLoginMessageLayout::TLoginMessageLayout(
			const string& aUserName,
			const string& aPassword,
			const string& aSecurity)
	: iUserName(aUserName)
	, iPassword(aPassword)
	, iSecurity(aSecurity)
		{ TRACE
		}

TLoginMessageLayout::TLoginMessageLayout()
	{ TRACE
	}
TLoginMessageLayout::~TLoginMessageLayout()
	{ TRACE
	}