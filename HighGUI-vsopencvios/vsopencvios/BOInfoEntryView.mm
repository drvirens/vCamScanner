//
//  BOInfoEntryView.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOInfoEntryView.h"

@interface BOInfoEntryView ()

@end

@implementation BOInfoEntryView

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super initWithCoder:aDecoder]) {
        [self commonInit];
    }
    return self;
}

- (void)commonInit {
    NSString* nibnamed = NSStringFromClass([self class]);
    BOInfoEntryView* weakView = (BOInfoEntryView*)[[[NSBundle mainBundle] loadNibNamed:nibnamed owner:self options:nil] firstObject];
    [self addSubview:weakView];
    weakView.frame = self.bounds;
}

@end
