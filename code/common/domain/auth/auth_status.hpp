//
//  auth_status.hpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/11/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef auth_status_hpp
#define auth_status_hpp

enum EAuthenticationStatus
	{
	EAuthenticationStatus_NotAuthenticated= (0x1 << 0),
	EAuthenticationStatus_WrongUserID			= (0x1 << 1),
	EAuthenticationStatus_WrongPassword		= (0x1 << 2),
	EAuthenticationStatus_Success					= (0x1 << 3),
	EAuthenticationStatus_Max							= (0x1 << 4)
	};

#endif /* auth_status_hpp */
