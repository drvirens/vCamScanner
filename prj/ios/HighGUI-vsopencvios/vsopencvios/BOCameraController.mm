//
//  BOCameraController.m
//  Bowen Swift
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import "BOCameraController.h"
#import "BOConstants.h"

#define return_from_block return

@interface BOCameraController ()
@property (nonatomic) AVCaptureSession* session;
@property (nonatomic) AVCaptureStillImageOutput* output;
@property (nonatomic, copy) CapturePhotoCompletion completion;
@property (nonatomic) AVCaptureDevice* device;
@property (nonatomic) BOOL toogleFlash;
@end

@implementation BOCameraController
#pragma mark - API

- (void)startCameraInView:(UIView*)view {
	[self checkAuthorized:view];
}

- (void)stopPreview {
    [self.session stopRunning];
    self.session = nil;
}
- (void)checkAuthorizationWithCompletion:( void(^)(VSCameraStatus) )completion {
    AVAuthorizationStatus status = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    switch (status) {
        case AVAuthorizationStatusNotDetermined: {
            [self statusNotDeterminedCompletion:completion];
        } break;
        case AVAuthorizationStatusRestricted: {
            [self statusRestrictedCompletion:completion];
        } break;
        case AVAuthorizationStatusDenied: {
            [self statusDeniedCompletion:completion];
        } break;
        case AVAuthorizationStatusAuthorized: {
            [self statusAuthorizedCompletion:completion];
        } break;
    }
}

- (void)requestPermissionsWithCompletion:( void(^)(BOOL) )completion {
    [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
        if (completion) {
            completion(granted);
        }
    }];
}

#pragma mark - utils
- (void)statusNotDeterminedCompletion:( void(^)(VSCameraStatus) )completion {
    if (completion) {
        completion(VSCameraStatusInDetermined);
    }
}
- (void)statusRestrictedCompletion:( void(^)(VSCameraStatus) )completion {
    if (completion) {
        completion(VSCameraStatusRestricted);
    }
}
- (void)statusDeniedCompletion:( void(^)(VSCameraStatus) )completion {
    if (completion) {
        completion(VSCameraStatusDenied);
    }
}
- (void)statusAuthorizedCompletion:( void(^)(VSCameraStatus) )completion {
    if (completion) {
        completion(VSCameraStatusAuthorized);
    }
}

#pragma mark - API
- (void)capturePhotoWithCompletion:(CapturePhotoCompletion)completion {
	if (!self.output) {
		NSLog(@"no output created");
		return;
	}
	
	self.completion = completion;
	
	__block AVCaptureConnection* connection = nil;
	NSArray<AVCaptureConnection*>* connections = [self.output connections];
	[connections enumerateObjectsUsingBlock:^(AVCaptureConnection * _Nonnull conn, NSUInteger idx, BOOL * _Nonnull stop) {
		if (conn) {
			NSArray<AVCaptureInputPort*>* ports = [conn inputPorts];
			[ports enumerateObjectsUsingBlock:^(AVCaptureInputPort * _Nonnull port, NSUInteger portidx, BOOL * _Nonnull portstop) {
				if (port) {
					if ([[port mediaType] isEqual:AVMediaTypeVideo]) {
						connection = conn;
						*portstop = YES;
						*stop = YES;
					}
				}
			}];
		}
	}];
	
	if (!connection) {
		NSLog(@"no connection");
		return;
	}
	
	[self.output captureStillImageAsynchronouslyFromConnection:connection completionHandler:^(CMSampleBufferRef imageDataSampleBuffer, NSError *error) {
		if (!error) {
			NSData* imageData = [AVCaptureStillImageOutput jpegStillImageNSDataRepresentation:imageDataSampleBuffer];
			UIImage* img = [UIImage imageWithData:imageData];
			if (img && self.completion) {
				dispatch_async(dispatch_get_main_queue(), ^{
					self.completion(img);
				});
			}
		}
	}];
}

#pragma mark - private
- (void)checkAuthorized:(UIView*)view {
	AVAuthorizationStatus status = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
	BOOL invokeSettings = NO;
	switch (status) {
		case AVAuthorizationStatusNotDetermined: {
			invokeSettings = NO;
		} break;
		case AVAuthorizationStatusRestricted: {
			NSLog(@"Not authroized");
			abort();
		} break;
		case AVAuthorizationStatusDenied: {
			invokeSettings = YES;
		} break;
		case AVAuthorizationStatusAuthorized: {
			NSLog(@"already have persmissions");
			[self createCaptureSession:view];
			return;
		};
	}
	
	if (invokeSettings) {
			//XXX - show dialog to take to system settings camera
	} else {
		typeof (self) __weak welf = self;
		[AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
			typeof (self) __strong strongSelf = welf;
			if (!strongSelf) {
				return_from_block;
			}
			if (granted) {
				dispatch_async(dispatch_get_main_queue(), ^{
					[strongSelf createCaptureSession:view];
				});
				
			} else {
				NSLog(@"user did not authroize us - show some dialog and stay on same screen");
					//XXX - what to do? specs???
			}
		}];
	}
}

- (void)createCaptureSession:(UIView*)view {
	if (self.session) {
		return;
	}
	self.session = [self doCrateCaptureSession:view];
	[self.session startRunning];
}


- (AVCaptureSession*)doCrateCaptureSession:(UIView*)view {
	if (_session) {
		return _session;
	}
	
	AVCaptureSession* session = nil;
	self.device = [self cameraForPosition:AVCaptureDevicePositionBack];
	//NSAssert(self.device != nil, @"device was nil");
	if (!self.device) {
		return session;
	}
	
	session = [[AVCaptureSession alloc] init]; //session queue
	
		//create input
	NSError* err = nil;
	AVCaptureDeviceInput* input = [[AVCaptureDeviceInput alloc] initWithDevice:self.device error:&err];
	if (err) {
		NSLog(@"could not get input device ");
		return session;
	}
	if ([session canAddInput:input]) {
		[session addInput:input];
	}
	
		//create output
	AVCaptureStillImageOutput* output = [[AVCaptureStillImageOutput alloc] init];
	if ([session canAddOutput:output]) {
		[session addOutput:output];
	}
	_output = output;
	
		//preview layer
	
	AVCaptureVideoPreviewLayer* video = [AVCaptureVideoPreviewLayer layerWithSession:session];
	
	dispatch_async(dispatch_get_main_queue(), ^{
//		CGRect r = [[UIScreen mainScreen] bounds];
//        r.size.height = r.size.height - kHeightLowerView;
//        UIView* cameraview = [[UIView alloc] initWithFrame:r];
        
        UIView* cameraview = [[UIView alloc] init];
		[view addSubview:cameraview];
		
		[cameraview.layer addSublayer:video];
		
		video.videoGravity = AVLayerVideoGravityResizeAspectFill;
		video.frame = view.bounds;
//		video.position=CGPointMake(CGRectGetMidX(r), CGRectGetMidY(r));
		
		[view sendSubviewToBack:cameraview];
	});
	
	return session;
}

- (AVCaptureDevice*)cameraForPosition:(AVCaptureDevicePosition)position {
	__block AVCaptureDevice* camera = nil;
	NSArray<AVCaptureDevice*>* cameras = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
	[cameras enumerateObjectsUsingBlock:^(AVCaptureDevice * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
		if (obj) {
			if ([obj position] == position) {
				camera = obj;
				*stop = YES;
			}
		}
	}];
	return camera;
}

- (BOOL)toggleCameraFlash {
    if ([self.device hasTorch] && [self.device position] == AVCaptureDevicePositionBack) {
        [self.device lockForConfiguration:nil];
        
        if(self.toogleFlash){
            [self.device setTorchMode:AVCaptureTorchModeOff];
        }
        else{
            [self.device setTorchMode:AVCaptureTorchModeOn];
        }
        
        [self.device unlockForConfiguration];
    }
    
    self.toogleFlash =! self.toogleFlash;
    return self.toogleFlash;
}

@end
