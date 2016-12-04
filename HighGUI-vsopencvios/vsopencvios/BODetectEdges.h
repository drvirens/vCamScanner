//
//  BODetectEdges.h
//  vsopencvios
//
//  Created by Virendra Shakya on 12/3/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MMCropView.h"

@interface BODetectEdges : NSObject
@property (nonatomic) MMCropView* croppedView;

- (void)apiDetectEdges:(UIImageView*)capturedImageView croppedView:(MMCropView*)croppedView;
@end
