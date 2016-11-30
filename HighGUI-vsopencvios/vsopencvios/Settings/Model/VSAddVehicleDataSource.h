//
//  VSAddVehicleDataSource.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/22/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>
@class VSVehicleAddFieldModel;

typedef NS_ENUM(NSInteger, VSETextFieldTag) {
	VSETextFieldTagMake,
	VSETextFieldTagModel,
	VSETextFieldTagYear,
	VSETextFieldTagPlate,
	VSETextFieldTagOdometer,
	VSETextFieldTagNickName,
	VSETextFieldTagPrimaryVehicle
};

@interface VSAddVehicleDataSource : NSObject
@property (nonatomic, readonly) NSMutableArray<VSVehicleAddFieldModel*>* dataSrc;
@end
