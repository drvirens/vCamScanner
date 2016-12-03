//
//  AppDelegate.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/18/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "AppDelegate.h"
#import "BOFacade.h"
#import "PhotoController.h"
#import "BOLocationController.h"
#import "UIViewController+BOUtils.h"

@interface AppDelegate ()
@property (nonatomic) BOFacade* facade;
@property (nonatomic) PhotoController *photoController;
@property (nonatomic, strong) BOLocationController *locationController;
@end

@implementation AppDelegate
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    self.photoController = [[PhotoController alloc] init];
    self.facade = [[BOFacade alloc] init];
    self.locationController = nil; //[[BOLocationController alloc] init]; // XXX - Location in Phase 2 - dont allocate else it will trigger location permissions
    
    [self.facade bootStrap];
    
    UIViewController* rootVC = self.window.rootViewController;
    [rootVC injectFacadeInViewController:rootVC what:self.facade];
    
    return YES;
}

@end
