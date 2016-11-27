//
//  BOCameraCaptureViewController.m
//  iSpyChallenge
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOCameraCaptureViewController.h"
#import "BOCameraController.h"
//#import "BOAddChallengeTableViewController.h"

#include "BOCameraUtil.hpp"

static void* gUserLoadContext = &gUserLoadContext;

@interface BOCameraCaptureViewController ()
@property (nonatomic) BOCameraController* cameraController;
@property (weak, nonatomic) IBOutlet UIButton *buttonCameraCapture;
@property (nonatomic) UIImage* image;
//@property (nonatomic) User* user;
@end

@implementation BOCameraCaptureViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	
	[self setupButton];
	
//	if (self.dataController.authenticatedUser != nil) { //already loaded
		[self startCamera];
//	} else { //not laoded - wait for it it load
//		[self registerKVO];
//	}
}

- (void)dealloc {
//	[self unregisterKVO];
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
		
			//XXX - do this on background thread
		NSData *theImageData = UIImageJPEGRepresentation(image, 0.7); // 0.7 is JPG quality;
		const void* imageData = [theImageData bytes];
		size_t imageSize = [theImageData length];
		didCapturePhoto(imageData, imageSize, 0);
		
		[self gotoAddScreen];
	}];
}



- (void)gotoAddScreen {
//	UIStoryboard* sb = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
//	BOAddChallengeTableViewController* destVC = (BOAddChallengeTableViewController*)[sb instantiateViewControllerWithIdentifier:@"BOAddChallengeTableViewController"];
//	destVC.capturedPic = self.image;
//	destVC.dataController = self.dataController;
//	destVC.photoController = self.photoController;
//	destVC.locationController = self.locationController;
//	destVC.user = self.user;
//		//[self presentViewController:destVC animated:YES completion:nil];
//	[self.navigationController pushViewController:destVC animated:YES];
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

#pragma mark - KVO
//- (void)registerKVO {
//	[self.dataController addObserver:self forKeyPath:NSStringFromSelector(@selector(authenticatedUser)) options:0 context:gUserLoadContext];
//}
//- (void)unregisterKVO {
//	@try {
//		[self.dataController removeObserver:self forKeyPath:NSStringFromSelector(@selector(authenticatedUser)) context:gUserLoadContext];
//	} @catch (NSException *exception) {
//		
//	}
//}
//- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context {
//	if (
//		[keyPath isEqualToString:NSStringFromSelector(@selector(authenticatedUser))] &&
//		[object isKindOfClass:[DataController class]] &&
//		context == gUserLoadContext
//		) {
//		self.user = [self.dataController authenticatedUser];
//		[self startCamera];
//	} else {
//		[super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
//	}
//}


@end
