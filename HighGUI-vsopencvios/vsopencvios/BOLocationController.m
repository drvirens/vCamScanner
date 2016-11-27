//
//  BOLocationController.m
//  iSpyChallenge
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Blue Owl. All rights reserved.
//

#import "BOLocationController.h"

@interface BOLocationController () <CLLocationManagerDelegate>
@property (nonatomic) CLLocationManager* locMgr;
@property (nonatomic) BOOL isStarted;
@end

@implementation BOLocationController


- (instancetype)init {
	if (self = [super init]) {
		[self commonInit];
	}
	return self;
}
- (void)commonInit {
	[self checkAuthorization];
}

- (void)checkAuthorization {
	CLAuthorizationStatus status = [CLLocationManager authorizationStatus];
	[self action:status];
}

- (void)action:(CLAuthorizationStatus)status {
	switch (status) {
		case kCLAuthorizationStatusNotDetermined: {
			[self.locMgr requestWhenInUseAuthorization];
		} break;
			
		case kCLAuthorizationStatusRestricted: {
			abort();
				//XXX - show some good fancy UI here and exit
		} break;
			
		case kCLAuthorizationStatusDenied: {
			NSLog(@"You did not give this persmission for location - go and check in settings");
			abort(); //XXX - take user to System Settings
		} break;
			
		case kCLAuthorizationStatusAuthorizedWhenInUse: {
			[self start];
		} break;
			
		case kCLAuthorizationStatusAuthorizedAlways: {
	  
		} break;
			
		default:
			break;
	}
}

#pragma mark - api
- (void)start {
	if (!self.isStarted) {
		[self.locMgr startUpdatingLocation];
	}
}
- (void)stop {
	if (self.isStarted) {
		[self.locMgr stopUpdatingLocation];
	}
}

#pragma mark - private

- (CLLocationManager*)locMgr {
	if (!_locMgr) {
		CLLocationManager* locmgr = [[CLLocationManager alloc] init];
		locmgr.desiredAccuracy = kCLLocationAccuracyBest; //TODO - needed???? - so we get th fix asap
		locmgr.delegate = self;
		
		_locMgr = locmgr;
	}
	return _locMgr;
}

#pragma mark - CLLocationManagerDelegate

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error {
	if (error) {
		NSLog(@"could not get location : %@", error);
	}
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations {
	self.poi = [locations lastObject];
}

- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status {
	[self action:status];
}

@end
