//
//  VSCameraPermissionsViewController.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 11/6/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BOCameraController.h"

@interface VSCameraPermissionsViewController : UIViewController
@property (nonatomic) BOCameraController* cameraController;
@property (nonatomic, copy) NSString* message;
@property (nonatomic, copy) NSString* positiveBtnTitle;
@end
