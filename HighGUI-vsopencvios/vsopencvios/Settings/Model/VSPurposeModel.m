//
//  VSPurposeModel.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSPurposeModel.h"

@interface VSPurposeModel ()
@property (nonatomic, readwrite) BOOL defaultPurpose;
@property (nonatomic, copy, readwrite) NSString* purposeName;
@end

@implementation VSPurposeModel
- (instancetype)initWithName:(NSString*)name isdefault:(BOOL)isdefault {
	if (self = [super init]) {
		_defaultPurpose = isdefault;
		_purposeName = name;
	}
	return self;
}
@end
