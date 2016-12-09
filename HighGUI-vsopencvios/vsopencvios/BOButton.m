//
//  BOButton.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/9/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOButton.h"

@implementation BOButton

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event {
    CGFloat margin = 35.0;
    CGRect area = CGRectInset(self.bounds, -margin, -margin);
    return CGRectContainsPoint(area, point);
}

@end
