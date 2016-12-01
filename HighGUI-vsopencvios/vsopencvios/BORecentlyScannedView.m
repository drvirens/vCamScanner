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

- (IBAction)didTapCloseButton:(id)sender {
    if ([self.delegate respondsToSelector:@selector(view:didTapCloseButton:)]) {
        [self.delegate view:self didTapCloseButton:sender];
    }
}

- (IBAction)didTapOnFirstScannedButton:(id)sender {
    if ([self.delegate respondsToSelector:@selector(view:didTapOnFirstScannedButton:)]) {
        [self.delegate view:self didTapOnFirstScannedButton:sender];
    }
}

- (IBAction)didTapOnSecondScannedButton:(id)sender {
    if ([self.delegate respondsToSelector:@selector(view:didTapOnSecondScannedButton:)]) {
        [self.delegate view:self didTapOnSecondScannedButton:sender];
    }
}

- (IBAction)didTapOnThirdScannedView:(id)sender {
    if ([self.delegate respondsToSelector:@selector(view:didTapOnThirdScannedView:)]) {
        [self.delegate view:self didTapOnThirdScannedView:sender];
    }
}

@end
