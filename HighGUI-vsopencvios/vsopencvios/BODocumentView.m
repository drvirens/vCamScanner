//
//  BODocumentView.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BODocumentView.h"

@implementation BODocumentView

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super initWithCoder:aDecoder]) {
        [self commonInit];
    }
    return self;
}

- (void)commonInit {
    NSString* nibnamed = NSStringFromClass([self class]);
    BODocumentView* weakView = (BODocumentView*)[[[NSBundle mainBundle] loadNibNamed:nibnamed owner:self options:nil] firstObject];
    [self addSubview:weakView];
    weakView.frame = self.bounds;
}

@end
