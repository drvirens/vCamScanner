//
//  BOCameraCaptureViewController.h
//  iSpyChallenge
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Blue Owl. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PhotoController.h"
#import "BOLocationController.h"

@interface BOCameraCaptureViewController : UIViewController
//@property (nonatomic, strong) DataController *dataController;
@property (nonatomic, strong) PhotoController *photoController;
@property (nonatomic, strong) BOLocationController *locationController;
@end
