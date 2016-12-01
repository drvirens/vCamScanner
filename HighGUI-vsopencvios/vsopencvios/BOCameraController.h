//
//  BOCameraController.h
//  Bowen Swift
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


typedef NS_ENUM(NSInteger, VSCameraStatus) {
    VSCameraStatusRestricted,
    VSCameraStatusDenied,
    VSCameraStatusInDetermined,
    VSCameraStatusAuthorized
};


typedef void(^CapturePhotoCompletion)(UIImage*);

@interface BOCameraController : NSObject

- (void)checkAuthorizationWithCompletion:( void(^)(VSCameraStatus) )completion;
- (void)requestPermissionsWithCompletion:( void(^)(BOOL) )completion;

- (void)startCameraInView:(UIView*)view;
- (void)stopPreview;
- (void)capturePhotoWithCompletion:(CapturePhotoCompletion)completion;
- (BOOL)toggleCameraFlash; // returns on/off. YES = on, NO = off
@end

