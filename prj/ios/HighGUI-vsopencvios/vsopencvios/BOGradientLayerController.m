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

//Metallic grey gradient background
+ (CAGradientLayer*) greyGradient {
    
    UIColor *colorOne		= [UIColor colorWithWhite:0.9 alpha:1.0];
    UIColor *colorTwo		= [UIColor colorWithHue:0.625 saturation:0.0 brightness:0.85 alpha:1.0];
    UIColor *colorThree	    = [UIColor colorWithHue:0.625 saturation:0.0 brightness:0.7 alpha:1.0];
    UIColor *colorFour		= [UIColor colorWithHue:0.625 saturation:0.0 brightness:0.4 alpha:1.0];
    
    NSArray *colors =  [NSArray arrayWithObjects:(id)colorOne.CGColor, colorTwo.CGColor, colorThree.CGColor, colorFour.CGColor, nil];
    
    NSNumber *stopOne		= [NSNumber numberWithFloat:0.0];
    NSNumber *stopTwo		= [NSNumber numberWithFloat:0.02];
    NSNumber *stopThree	    = [NSNumber numberWithFloat:0.99];
    NSNumber *stopFour		= [NSNumber numberWithFloat:1.0];
    
    NSArray *locations = [NSArray arrayWithObjects:stopOne, stopTwo, stopThree, stopFour, nil];
    
    CAGradientLayer *headerLayer = [CAGradientLayer layer];
    headerLayer.colors = colors;
    headerLayer.locations = locations;
    
    return headerLayer;
}

@end
