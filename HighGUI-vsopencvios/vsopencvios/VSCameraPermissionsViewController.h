//
//  VSCameraPermissionsViewController.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 11/6/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BOCameraController.h"

@class VSCameraPermissionsViewController;
@protocol VSCameraPermissionsViewControllerDelegate <NSObject>
- (void)vc:(VSCameraPermissionsViewController*)vc hasCameraPermissions:(BOOL)hasPermissions;
@end

@interface VSCameraPermissionsViewController : UIViewController
@property (nonatomic, weak) id<VSCameraPermissionsViewControllerDelegate> delegate;
@property (nonatomic) BOCameraController* cameraController;
@property (nonatomic, copy) NSString* message;
@property (nonatomic, copy) NSString* positiveBtnTitle;
@end
