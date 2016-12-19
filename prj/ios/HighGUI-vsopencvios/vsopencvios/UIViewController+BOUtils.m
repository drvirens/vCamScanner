//
//  UIViewController+FacadeUtils.m
//  Awesome Sauce
//
//  Created by Virendra Shakya on 9/30/16.
//
//

#import "UIViewController+BOUtils.h"

@implementation UIViewController (BOUtils)
- (void)injectFacadeInViewController:(UIViewController*)rootVC what:(id)what {
    UIViewController* bottom = nil; //the one who gets injected
    
    if ([rootVC isKindOfClass:[UINavigationController class]]) {
        UINavigationController* navVC = (UINavigationController*)rootVC;
        UIViewController* firstVC = [[navVC viewControllers] firstObject];
        
        bottom = firstVC;
    } else if ([rootVC isKindOfClass:[UITabBarController class]]) {
    } else { //regular ViewController
        bottom = rootVC;
    }
    
    if (bottom) {
        //facade
        SEL setFacade = NSSelectorFromString(@"setFacade:");
        [self inject:bottom what:what selector:setFacade];
        
        //photoController
        SEL setBOPhotoController = NSSelectorFromString(@"setBOPhotoController:");
        [self inject:bottom what:what selector:setBOPhotoController];
        
        //locationController
        SEL setLocationController = NSSelectorFromString(@"setLocationController:");
        [self inject:bottom what:what selector:setLocationController];
    }
}

- (void)inject:(UIViewController*)vc what:(id)what selector:(SEL)selector {
    if (vc && [vc respondsToSelector:selector]) {
        id facadeObj = what;
        if (facadeObj) {
            IMP imp = [vc methodForSelector:selector];
            void(*fn)(id, SEL, id) = (void*)imp;
            fn(vc, selector, facadeObj);
        }
    }
}

@end
