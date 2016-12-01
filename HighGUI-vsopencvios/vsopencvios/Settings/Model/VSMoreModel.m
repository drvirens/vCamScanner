//
//  VSMoreModel.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSMoreModel.h"

@interface VSMoreModel ()
@property (nonatomic, copy, readwrite ) NSString* title;
@property (nonatomic, copy, readwrite ) NSString* subTitle;
@property (nonatomic, copy, readwrite ) NSString* iconName;
@end

@implementation VSMoreModel
- (instancetype)initWithTitle:(NSString*)title subTitle:(NSString*)subTitle iconName:(NSString*)iconName {
	if (self = [super init]) {
		_title = title;
		_subTitle = subTitle;
		_iconName = iconName;
	}
	return self;
}
@end
