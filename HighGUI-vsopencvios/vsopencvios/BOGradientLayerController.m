//
//  BOGradientLayerController.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOGradientLayerController.h"
#import "VSBranding.h"

@implementation BOGradientLayerController
+ (CAGradientLayer*)blackGradient {
    NSArray* colors = @[
                        (id)[UIColor darkGrayColor].CGColor,
                        //(id)[UIColor greenColor].CGColor,
                        (id)[UIColor blackColor].CGColor
                        ];
    
    NSArray* locations = @[
                           [NSNumber numberWithFloat:0.f],
                           //[NSNumber numberWithFloat:0.5f],
                           [NSNumber numberWithFloat:1.f]
                           ];
    CAGradientLayer* ret = [CAGradientLayer layer];
    ret.colors = colors;
    //ret.locations = locations;
    return ret;
}
@end
