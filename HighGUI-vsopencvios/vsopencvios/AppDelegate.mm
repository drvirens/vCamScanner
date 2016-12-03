//
//  AppDelegate.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/18/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "AppDelegate.h"
//test+
#include "app_server.hpp"
#include "trace.h"
#include "lmdb.h"
//test-

@interface AppDelegate ()

@end

@implementation AppDelegate
{
    CAppServer* app_;
}

//test+
- (void)testLMDB {
    MDB_env* iEnv;
    
    unsigned long aSize = 1024 * 1024;
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

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
    NSString *libraryDirectory = [paths objectAtIndex:0];
    string path = [libraryDirectory UTF8String];
    
    app_ = new CAppServer(path);
    app_->createRepository();
    
    app_->addAwesomeSauceAndViren();
    
    auto blockAuthCompletion = [&](const EAuthenticationStatus& aEAuthenticationStatus,
                                   const vsUser& aAuthenticatedUser)
    {
        //comletionAuthenticate(aEAuthenticationStatus, aAuthenticatedUser);
        LOG("dont care if it fails for now");
    };

    app_->authenticate(blockAuthCompletion);
    
//    [self testLMDB];
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
