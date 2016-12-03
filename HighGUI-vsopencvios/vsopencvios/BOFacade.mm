//
//  BOFacade.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/3/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOFacade.h"
#include "app_server.hpp"
#include "model_immutable_login.hpp"
#include "trace.h"

@interface BOFacade ()

@end

@implementation BOFacade {
    CAppServer* app_;
}

- (void)bootStrap {
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
    TLoginMessageLayout credentials; // XXX
    app_->authenticate(credentials, blockAuthCompletion);
}

@end
