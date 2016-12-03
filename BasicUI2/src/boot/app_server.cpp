//
//  app_server.cpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/11/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "app_server.hpp"
#include "trace.h"
#include "repository_impl.hpp"
#include "user.hpp"
#include "auth_status.hpp"
#include "model_immutable_login.hpp"
#include "authenticator_impl.hpp"
#include "user.hpp"

CAppServer::CAppServer(const string& aPath)
	: iPath(aPath)
	{ TRACE
	construct(aPath);
	}

CAppServer::~CAppServer()
	{ TRACE
	}

void CAppServer::start()
	{ TRACE
	}

void CAppServer::stop()
	{ TRACE
	}

void CAppServer::construct(const string& aPath)
	{ TRACE
	}

void CAppServer::createRepository()
	{
    unsigned long size = 1 * 1024 * 1024;
	ASSERT(iPath.length() > 0);
	iKeyValueStore = make_shared< vsKeyValueStore >(iPath, size);
	iRepository = make_shared<vsRepository>(*iKeyValueStore.get());
	SignalDidCreateKeyStore(iRepository);
        
    iAuthenticator = make_shared<CAuthenticator>(*(iRepository.get()));
	}

void CAppServer::addAwesomeSauceAndViren()
{ TRACE
    string theUserName				= "viren@india.com";
    string theFullName				= "virendra shakya";
    string theEMail					= "virendra@skully.com";
    string thePassword				= "virenpassword";
    string theSecurity				= "viren-security-plain";
    addUser(iRepository, theUserName, theFullName, theEMail, thePassword, theSecurity);
    
    theUserName                     = "awesomeSauce";
    theFullName                     = "daniel watts";
    theEMail                        = "awesome@sauce.com";
    thePassword                     = "awesomesaucePassword";
    theSecurity                     = "SASL";
    addUser(iRepository, theUserName, theFullName, theEMail, thePassword, theSecurity);
}

void CAppServer::addUser(shared_ptr<vsIRepository> aKeyStoreRepositry,
                                 string theUserName,
                                 string theFullName,
                                 string theEMail,
                                 string thePassword,
                                 string theSecurity)
{ TRACE
    long theCreationDate			= 0;
    long theModificationDate        = 0;
    vsUser user(theUserName, theFullName, theEMail, thePassword, theSecurity, theCreationDate, theModificationDate);
    aKeyStoreRepositry->put(user, [](const vsModelBase& aPuttedModel)
                            {
                                LOG("\t Did successfully put the model [%s] \n", aPuttedModel.primaryKey().c_str());
                            });
}

void CAppServer::authenticate(function< void(const EAuthenticationStatus&, const vsUser&) > aSignalDidAuthenticateUser)
{
    TLoginMessageLayout credentials; //XXX
    iAuthenticator->authenticate(credentials, aSignalDidAuthenticateUser);
}

