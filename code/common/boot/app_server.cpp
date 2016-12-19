//
//  app_server.cpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/11/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include <sstream>
#include "app_server.hpp"
#include "trace.h"
#include "repository_impl.hpp"
#include "user.hpp"
#include "auth_status.hpp"
#include "model_immutable_login.hpp"
#include "authenticator_impl.hpp"
#include "user.hpp"
#include "document.hpp"
#include "time_utils.hpp"
#include "document_record_creiterion.hpp"
#include "primary_key.hpp"

using namespace std;

CAppServer::CAppServer(const string& aPath)
	: iPath(aPath)
    , iSessionID_(1)
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

void CAppServer::authenticate(TLoginMessageLayout& aCredentials,
                              function< void(const EAuthenticationStatus&, const vsUser&) > aSignalDidAuthenticateUser)
    { TRACE
    iAuthenticator->authenticate(aCredentials, aSignalDidAuthenticateUser);
    }

void CAppServer::addDocument(vsDocument& aDocument, function< void(const vsDocument&) > aSignalDidSaveDocuemnt)
    { TRACE
    iRepository->put(aDocument, [](const vsModelBase& aPuttedModel)
                            {
                                LOG("\t Did successfully put the model [%s] \n", aPuttedModel.primaryKey().c_str());
                            });
    }
    
void CAppServer::getAllDocuments(vsLinkedList<const vsModelBase>& aLinkedList,
            function<void()> aCompletion)
    { TRACE
    vsPrimaryKey* docIDLower = new vsPrimaryKey("1"); //XXX - vsDocument should accept the docID from outside instead of generating automatically
    
    vsTData* theKeyLowerBound = new vsTData();
    docIDLower->wrappedPrimaryKey(*theKeyLowerBound);
    
    vsPrimaryKey* docIDUpper = new vsPrimaryKey("3");
    vsTData* theKeyUpperBound = new vsTData();
    docIDUpper->wrappedPrimaryKey(*theKeyUpperBound);
    
    vsIKeyValueReader::vsDirection theDirection = vsIKeyValueReader::vsDirectionForward;
    vsRecordCreiterion* criteria = new vsDocumentRecordCreiterion(*theKeyLowerBound, *theKeyUpperBound, theDirection);
    
    iRepository->getAll(*criteria,
                        [&](vsLinkedList<const vsModelBase>& aCollection) {
                            LOG("\n Completion function -  \n");
//                            aCollection.traverse(visitNode);
                            aLinkedList = aCollection;
                            aCompletion();
                        });
    }

void CAppServer::generateImageName(const string& aLabel, string& aOutput)
    { TRACE
    string timeNow;
    ::currentTime(timeNow);
    stringstream ss;
    ss << "img_" << aLabel << "_" << iSessionID_++ << "_" << timeNow;
    aOutput = ss.str();
    }

void CAppServer::generateDefaultDocTitle(const string& aLabel, string& aOutput)
    { TRACE
    // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    stringstream ss;
    ss << aLabel << "_" << buf;
    aOutput = ss.str();
    }

