//
//  BOCameraController.h
//  Bowen Swift
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef void(^CapturePhotoCompletion)(UIImage*);

@interface BOCameraController : NSObject
- (void)startCameraInView:(UIView*)view;
- (void)stopCamera;
- (void)capturePhotoWithCompletion:(CapturePhotoCompletion)completion;
- (BOOL)toggleCameraFlash; // returns on/off. YES = on, NO = off
@end

