//
//  AppDelegate.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/18/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "AppDelegate.h"
#include "app_server.hpp"
#include "trace.h"

@interface AppDelegate ()
@end

@implementation AppDelegate
{
    CAppServer* app_;
}
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
    NSString *libraryDirectory = [paths objectAtIndex:0];
    string path = [libraryDirectory UTF8String];
    app_ = new CAppServer(path);
    app_->createRepository();
    app_->addAwesomeSauceAndViren();
    auto blockAuthCompletion = [&](const EAuthenticationStatus& aEAuthenticationStatus, const vsUser& aAuthenticatedUser)
    {
        LOG("dont care if it fails for now");
    };
    app_->authenticate(blockAuthCompletion);
    return YES;
}
#if 0
//test+
#include "lmdb.h"
- (void)testLMDB {
    MDB_env* iEnv = 0;
    unsigned long aSize = 1 * 1024 * 1024;
    int status = mdb_env_create(&iEnv);
    if (MDB_SUCCESS != status)
    {
        NSLog(@"\t could not create mdb_env_create \n");
        return;
    }
    status = mdb_env_set_mapsize(iEnv, aSize);
    if (MDB_SUCCESS != status) { NSLog(@"mdb_env_set_mapsize failed: %d", status); return;}
    status = mdb_env_set_maxdbs(iEnv, 64);
    if (MDB_SUCCESS != status) { NSLog(@"mdb_env_set_maxdbs failed: %d", status); return;}
    //viren+
    //fileUtil_ = new BOFileUtil_iOS();
    //string path = fileUtil_->getWritablePath();
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
    NSString *libraryDirectory = [paths objectAtIndex:0];
    string path = [libraryDirectory UTF8String];
    char* virenTEST = new char[path.length() + 1];
    strcpy(virenTEST, path.c_str());
    status = mdb_env_open(iEnv, virenTEST, MDB_NOLOCK, 0664);
    //viren-
    //		status = mdb_env_open(iEnv, iPath.c_str(), MDB_NOSYNC, 0664);
    if (MDB_SUCCESS != status) { NSLog(@"mdb_env_open failed: %d", status); return;}
    int removeReaders = 0;
    status = mdb_reader_check(iEnv, &removeReaders);
    if (removeReaders)
    {
        NSLog(@"\t removed [%d] stale readers\n", removeReaders);
    }
}
//test-
#endif
@end
