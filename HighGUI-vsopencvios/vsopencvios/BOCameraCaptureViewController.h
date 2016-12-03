//
//  BOCameraCaptureViewController.h
//  Bowen Swift
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BOFacade.h"
#import "PhotoController.h"
#import "BOLocationController.h"
 
@interface BOCameraCaptureViewController : UIViewController
@property (nonatomic) BOFacade* facade;
@property (nonatomic) PhotoController *photoController;
@property (nonatomic, strong) BOLocationController *locationController;
@end
