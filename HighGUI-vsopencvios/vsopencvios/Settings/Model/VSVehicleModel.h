//
//  VSVehicleModel.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VSVehicleModel : NSObject
@property (nonatomic, readonly) BOOL defaultVehicle;
@property (nonatomic, copy, readonly) NSString* vehicleName;
@property (nonatomic, copy, readonly) NSString* vehicleOdometerReadings;

- (instancetype)initWithName:(NSString*)name odometer:(NSString*)odometer isdefault:(BOOL)isdefault;
@end
