//
//  VSVehicleAddFieldModel.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/20/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSVehicleAddFieldModel.h"

@interface VSVehicleAddFieldModel ()
@property (nonatomic, copy, readwrite) NSString* title;
@property (nonatomic, copy, readwrite) NSString* placeHolder;
@property (nonatomic, readwrite) NSInteger tag;
@end

@implementation VSVehicleAddFieldModel
- (instancetype)initWithTitle:(NSString*)title placeHolder:(NSString*)placeHolder tag:(NSInteger)tag {
	if (self = [super init]) {
		_title = title;
		_placeHolder = placeHolder;
		_tag = tag;
	}
	return self;
}
@end
