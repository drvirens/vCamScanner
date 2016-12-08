//
//  authenticator_impl.cpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/10/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "authenticator_impl.hpp"
#include "user.hpp"
#include "model_immutable_login.hpp"
#include "repository.hpp"
#include "trace.h"
#include "document_record_creiterion.hpp"
#include "primary_key.hpp"

CAuthenticator::CAuthenticator(vsIRepository& avsIRepository)
	{ TRACE
	iRepository.reset(&avsIRepository);
	}

CAuthenticator::~CAuthenticator()
	{ TRACE
	}

static void visitNode(void* aData)
    {
    vsDocument* doc = (vsDocument*)aData;
    if (doc) 
        {
        LOG("\n got docuemnt \n");
        }
    }
void CAuthenticator::authenticate(const TLoginMessageLayout& credentials,
			function<void(const EAuthenticationStatus&, const vsUser&)> aCompletionCB)
	{ TRACE
    
//	vsUser objGetuser(credentials.userName());
//	iRepository->get(objGetuser, [&](const vsModelBase& aModel)
//		{
//		EAuthenticationStatus status = EAuthenticationStatus_Success;
//		const vsUser& retUser = dynamic_cast<const vsUser&>(aModel) ;
//		LOG("\t did authenticate user dumped below: \n");
//		retUser.debugDump();
//		
//		aCompletionCB(status, retUser);
//		});
        
        
        
        //test+
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
                            aCollection.traverse(visitNode);
                        });
        //test-
        
	}



