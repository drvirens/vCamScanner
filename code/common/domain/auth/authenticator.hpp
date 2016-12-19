//
//  authenticator.hpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/10/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef authenticator_hpp
#define authenticator_hpp

#include <functional>
#include <memory>
#include "auth_status.hpp"

using namespace std;
class IAuthenticator;
//class TUser;
class TLoginMessageLayout;
class vsUser;

//typedef void (*CBAuthenticate)(IAuthenticator*, EAuthenticationStatus, void*, const TLoginMessageLayout&);

class IAuthenticator
	{
public:
	IAuthenticator();
	virtual ~IAuthenticator();
	
//	virtual shared_ptr<TUser> authenticatedUser() = 0;
//	virtual void authenticate(const TLoginMessageLayout& credentials, CBAuthenticate cb, void* aData) = 0;
	
	virtual void authenticate(const TLoginMessageLayout& credentials,
			function<void(const EAuthenticationStatus&, const vsUser&)> aCompletionCB) = 0;
	};

#endif /* authenticator_hpp */
