//
//  VSVehicleAddFieldModel.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/20/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VSVehicleAddFieldModel : NSObject
@property (nonatomic, copy, readonly) NSString* title;
@property (nonatomic, copy, readonly) NSString* placeHolder;
@property (nonatomic, readonly) NSInteger tag;
- (instancetype)initWithTitle:(NSString*)title placeHolder:(NSString*)placeHolder tag:(NSInteger)tag;
@end
