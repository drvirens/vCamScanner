//
//  VSVehicleModel.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSVehicleModel.h"

@interface VSVehicleModel ()
@property (nonatomic, readwrite ) BOOL defaultVehicle;
@property (nonatomic, copy, readwrite ) NSString* vehicleName;
@property (nonatomic, copy, readwrite ) NSString* vehicleOdometerReadings;
@end

@implementation VSVehicleModel
- (instancetype)initWithName:(NSString*)name odometer:(NSString*)odometer isdefault:(BOOL)isdefault {
	if (self = [super init]) {
		_defaultVehicle = isdefault;
		_vehicleName = name;
		_vehicleOdometerReadings = odometer;
	}
	return self;
}
@end
