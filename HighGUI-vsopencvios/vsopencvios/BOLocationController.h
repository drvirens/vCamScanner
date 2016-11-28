//
//  BOLocationController.h
//  iSpyChallenge
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>

@interface BOLocationController : NSObject

@property (nonatomic) CLLocation* poi;

- (instancetype)init;
- (void)start;
- (void)stop;

@end
