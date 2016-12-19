//
//  authenticator_impl.hpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/10/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef authenticator_impl_hpp
#define authenticator_impl_hpp

#include "authenticator.hpp"

class vsIRepository;

class CAuthenticator : public IAuthenticator
	{
public:
	CAuthenticator(vsIRepository& avsIRepository);
	virtual ~CAuthenticator();
	
	virtual void authenticate(const TLoginMessageLayout& credentials,
			function<void(const EAuthenticationStatus&, const vsUser&)> aCompletionCB);
	
private:
	unique_ptr<vsIRepository> iRepository;
	};

#endif /* authenticator_impl_hpp */
