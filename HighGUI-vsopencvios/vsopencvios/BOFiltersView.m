//
//  BOFiltersView.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOFiltersView.h"

@interface BOFiltersView ()

@end

@implementation BOFiltersView

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super initWithCoder:aDecoder]) {
        [self commonInit:aDecoder];
    }
    return self;
}

- (void)commonInit:(NSCoder *)aDecoder {
    NSString* nib = NSStringFromClass([self class]);
    BOFiltersView* weakView = (BOFiltersView*)[[[NSBundle mainBundle] loadNibNamed:nib owner:self options:nil] firstObject];
    weakView.frame = self.bounds;
    [self addSubview:weakView];
}

@end
