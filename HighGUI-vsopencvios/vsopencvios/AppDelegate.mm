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
    self.locationController = nil; //[[BOLocationController alloc] init];
    
    UIViewController* rootVC = self.window.rootViewController;
    [rootVC injectFacadeInViewController:rootVC what:self.facade];
    
    return YES;
}

- (void)injectPropertiesInController:(UIViewController *)controller {
    if ([controller respondsToSelector:@selector(setFacade:)]) {
        [controller performSelector:@selector(setFacade:) withObject:self.facade];
    }
    if ([controller respondsToSelector:@selector(setPhotoController:)]) {
        [controller performSelector:@selector(setPhotoController:) withObject:self.photoController];
    }
    if ([controller respondsToSelector:@selector(setLocationController:)]) {
        [controller performSelector:@selector(setLocationController:) withObject:self.locationController];
    }
}

@end
