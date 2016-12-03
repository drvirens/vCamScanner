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
#include "chat_types.h"
#include "document.hpp"

class vsIRepository;
class vsIKeyValueStore;
class CAuthenticator;
class vsUser;
class vsDocument;
class TLoginMessageLayout;

using namespace std;
using namespace sigslot;

class CAppServer : public has_slots<>
	{
public:
	CAppServer(const string& aPath);
	virtual ~CAppServer();
    
    void start();
    void stop();
        
	void createRepository();
    void addAwesomeSauceAndViren(); // XXX - for Phase 1 - this is hardCoded
        
    void authenticate(TLoginMessageLayout& aCredentials,
                      function< void(const EAuthenticationStatus&, const vsUser&) > aSignalDidAuthenticateUser);
        
    void addDocument(vsDocument& aDocument, function< void() > aSignalDidSaveDocuemnt);
        
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
