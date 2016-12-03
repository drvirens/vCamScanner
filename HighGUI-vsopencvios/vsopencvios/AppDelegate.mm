//
//  AppDelegate.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/18/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "AppDelegate.h"
#import "BOFacade.h"
#import "UIViewController+BOUtils.h"

@interface AppDelegate ()
@property (nonatomic) BOFacade* facade;
@end

@implementation AppDelegate
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    self.facade = [[BOFacade alloc] init];
    
    [self.facade bootStrap];
    
    UIViewController* rootVC = self.window.rootViewController;
    [rootVC injectFacadeInViewController:rootVC what:self.facade];
    
    return YES;
}

@end
