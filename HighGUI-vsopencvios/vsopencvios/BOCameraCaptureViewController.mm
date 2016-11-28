//
//  BOCameraCaptureViewController.m
//  iSpyChallenge
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOCameraCaptureViewController.h"
#import "BOCameraController.h"

#include "file_utils_wrapper.h"
#include "scannerLite.h"

static void* gUserLoadContext = &gUserLoadContext;

@interface BOCameraCaptureViewController ()
@property (nonatomic) BOCameraController* cameraController;
@property (weak, nonatomic) IBOutlet UIButton *buttonCameraCapture;

@property (weak, nonatomic) IBOutlet UIView *containerCapturedView;
@property (weak, nonatomic) IBOutlet UIImageView *capturedImageView;
@property (weak, nonatomic) IBOutlet UIView *lowerContainerCapturedView;

@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *activityIndicator;

@property (nonatomic) UIImage* image;
@end

@implementation BOCameraCaptureViewController
- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
	if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
		
	}
	return self;
}
- (void)viewDidLoad {
    [super viewDidLoad];
	[self setupContainerView];
	[self setupButton];
	[self startCamera];
}
- (void)setupContainerView {
	self.containerCapturedView.hidden = YES;
}
- (void)setupButton {
	self.buttonCameraCapture.layer.borderColor = [UIColor whiteColor].CGColor;
	self.buttonCameraCapture.layer.borderWidth = 6.f;
	self.buttonCameraCapture.layer.cornerRadius = 50.f; //XXX hardcoded for now
}
- (IBAction)didTapCapturePhoto:(id)sender {
	typeof (self) __weak welf = self;
	[self.cameraController capturePhotoWithCompletion:^(UIImage * image) {
		NSLog(@"did capture ");
		welf.image = image;
		
		[welf showCapturedImage];
		
			//XXX - do this on background thread
		NSData *theImageData = UIImageJPEGRepresentation(image, 0.7); // 0.7 is JPG quality;
		const void* imageData = [theImageData bytes];
		size_t imageSize = [theImageData length];
		
		storeCapturedImage(imageData, imageSize);
		
		[self gotoAddScreen];
	}];
}
- (void)showCapturedImage {
	typeof (self) __weak welf = self;
	dispatch_async(dispatch_get_main_queue(), ^{
		typeof (self) __strong strongSelf = welf;
		if (strongSelf) {
			[strongSelf doShowCapturedImage];
		}
	});
}
- (void)doShowCapturedImage {
	self.containerCapturedView.hidden = NO;
		//self.capturedImageView.image = self.image;
	self.activityIndicator.hidden = NO;
}
- (void)gotoAddScreen {
}
#pragma mark - show camera
- (void)startCamera {
	[self.cameraController startCameraInView:self.view];
}
- (BOCameraController*)cameraController {
	if (!_cameraController) {
		BOCameraController* cc = [[BOCameraController alloc] init];
		
		_cameraController = cc;
	}
	return _cameraController;
}
- (BOOL)prefersStatusBarHidden {
	return YES;
}
@end
