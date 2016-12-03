//
//  app_server.hpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/11/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef app_server_hpp
#define app_server_hpp

#include <memory>
#include <string>
#include "sigslot.h"
#include "auth_status.hpp"

class vsIRepository;
class vsIKeyValueStore;
class CAuthenticator;
class vsUser;

using namespace std;
using namespace sigslot;

class CAppServer : public has_slots<>
	{
public:
	CAppServer(const string& aPath);
	virtual ~CAppServer();
	void createRepository();
    void addAwesomeSauceAndViren(); //for Phase 1 - this is hardCoded
    void authenticate(function< void(const EAuthenticationStatus&, const vsUser&) > aSignalDidAuthenticateUser);
        
	void start();
	void stop();
	
	signal1< shared_ptr<vsIRepository> > SignalDidCreateKeyStore;
	
private:
	void construct(const string& aPath);
    void addUser(shared_ptr<vsIRepository> aKeyStoreRepositry,
                 string theUserName,
                 string theFullName,
                 string theEMail,
                 string thePassword,
                 string theSecurity);
	
private:
	shared_ptr<vsIKeyValueStore> iKeyValueStore;
	shared_ptr<vsIRepository> iRepository;
	string iPath;
    shared_ptr<CAuthenticator> iAuthenticator;
	};

#endif /* app_server_hpp */
