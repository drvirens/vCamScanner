//
//  UIViewController+FacadeUtils.h
//  Awesome Sauce
//
//  Created by Virendra Shakya on 9/30/16.
//
//

#import <UIKit/UIKit.h>

@interface UIViewController (BOUtils)
//what = what object is being injected?
- (void)injectFacadeInViewController:(UIViewController*)rootVC what:(id)what;
@end
