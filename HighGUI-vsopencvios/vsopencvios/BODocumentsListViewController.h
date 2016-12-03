//
//  BODocumentsListViewController.h
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BOFacade.h"
#import "PhotoController.h"
#import "BOLocationController.h"

@interface BODocumentsListViewController : UIViewController
@property (nonatomic) BOFacade* facade;
@property (nonatomic) PhotoController *photoController;
@property (nonatomic, strong) BOLocationController *locationController;
@end
