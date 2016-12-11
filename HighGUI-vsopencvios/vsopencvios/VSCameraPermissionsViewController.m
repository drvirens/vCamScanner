//
//  VSCameraPermissionsViewController.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 11/6/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//


#import "VSCameraPermissionsViewController.h"
#import "BOCameraCaptureViewController.h"
#import "VSBranding.h"

@interface VSCameraPermissionsViewController ()
@property (weak, nonatomic) IBOutlet UILabel *labelMessage;
@property (weak, nonatomic) IBOutlet UIImageView *imageViewIcon;
@property (weak, nonatomic) IBOutlet UIButton *buttonPositive;
@end

@implementation VSCameraPermissionsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	
	self.labelMessage.text = self.message;
	[self.buttonPositive setTitle:self.positiveBtnTitle forState:UIControlStateNormal];
	
	UIImage* img = [UIImage imageNamed:@"ic_photo_camera_white"];
	//img = [img imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
	self.imageViewIcon.image = img;
	//self.imageViewIcon.tintColor = [VSBranding vs_darkGrayColor];
}

- (BOOL)prefersStatusBarHidden {
	return YES;
}

#pragma mark - button handlers
- (IBAction)didTapOnCancelButton:(id)sender {
	[self dismissViewControllerAnimated:YES completion:nil];
}
- (IBAction)didTapOnProceedButton:(id)sender {
	if ([self.positiveBtnTitle isEqualToString:@"Open Camera Settings"]) { //XXX constant
		NSURL *url = [NSURL URLWithString:UIApplicationOpenSettingsURLString];
		[[UIApplication sharedApplication] openURL:url];
		[self dismissViewControllerAnimated:YES completion:nil];
		return;
	}
	
	if ([self.positiveBtnTitle isEqualToString:@"OK"]) {
		return;
	}
	
	typeof (self) __weak welf = self;
	[self.cameraController requestPermissionsWithCompletion:^(BOOL granted) {
		dispatch_async(dispatch_get_main_queue(), ^{
			typeof (self) __strong strongSelf = welf;
			if (strongSelf) {        
                if ([self.delegate respondsToSelector:@selector(vc:hasCameraPermissions:)]) {
                    [self.delegate vc:self hasCameraPermissions:granted];
                }
                [self dismissViewControllerAnimated:YES completion:nil];
			}
		});
	}];
}


@end
