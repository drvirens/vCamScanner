//
//  BOGradientLayerController.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOGradientLayerController.h"

@implementation BOGradientLayerController
+ (CAGradientLayer*)blackGradient {
    NSArray* colors = @[
                        (id)[UIColor redColor].CGColor,
                        (id)[UIColor greenColor].CGColor,
                        (id)[UIColor blueColor].CGColor
                        ];
    
    NSArray* locations = @[
                           [NSNumber numberWithFloat:0.2f],
                           [NSNumber numberWithFloat:0.5f],
                           [NSNumber numberWithFloat:0.8f]
                           ];
    CAGradientLayer* ret = [CAGradientLayer layer];
    ret.colors = colors;
    //ret.locations = locations;
    return ret;
}
@end
