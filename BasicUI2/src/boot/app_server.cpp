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
	}
