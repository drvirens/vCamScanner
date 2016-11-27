//
//  BOCameraCaptureViewController.m
//  iSpyChallenge
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Blue Owl. All rights reserved.
//

#include <stdio.h>

#import "BOCameraCaptureViewController.h"
#import "BOCameraController.h"
//#import "BOAddChallengeTableViewController.h"

#define BUFLEN 512

static char *camera_directory = NULL;

	// Callback function invoked for every captured frame.
static void _camera_capturing_cb(const void* image_data, size_t image_size, void *user_data)
{
	if (NULL == image_data) {
		return;
	}
	char *file_path = (char *)malloc(sizeof(char) * BUFLEN);
	
		// Create a full path to newly created file for storing the taken photo.
	snprintf(file_path, BUFLEN, "%s/cam%d.jpg", camera_directory, (int)time(NULL));
	
		// Open the file for writing.
	FILE *file = fopen(file_path, "w+");
	
		// Write the image to a file.
	fwrite(image_data, 1, image_size, file);
	
		// Close the file.
	fclose(file);
}

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
