//
//  BORecentlyScannedView.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/30/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BORecentlyScannedView.h"

@implementation BORecentlyScannedView

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super initWithCoder:aDecoder]) {
        [self commonInit];
    }
    return self;
}

- (void)commonInit {
    NSString* nibnamed = NSStringFromClass([self class]);
    BORecentlyScannedView* weakView = (BORecentlyScannedView*)[[[NSBundle mainBundle] loadNibNamed:nibnamed owner:self options:nil] firstObject];
    [self addSubview:weakView];
    weakView.frame = self.bounds;
}

@end
