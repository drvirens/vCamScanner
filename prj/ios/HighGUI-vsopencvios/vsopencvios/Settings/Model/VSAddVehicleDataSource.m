//
//  VSAddVehicleDataSource.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/22/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSAddVehicleDataSource.h"
#import "VSSettingsConstants.h"
#import "VSVehicleAddFieldModel.h"

@interface VSAddVehicleDataSource ()
@property (nonatomic, readwrite) NSMutableArray<VSVehicleAddFieldModel*>* dataSrc;
@end

@implementation VSAddVehicleDataSource
- (instancetype)init {
	if (self = [super init]) {
		[self commonInit];
	}
	return self;
}
- (void)commonInit {
	[self setupDataSrc];
}

- (void)setupDataSrc {
	self.dataSrc = [NSMutableArray array];
	
	[self addModelWithText:kTextTitleMake placeHolder:kTextPlaceholderMake tag:VSETextFieldTagMake];
	[self addModelWithText:kTextTitleModel placeHolder:kTextPlaceholderModel tag:VSETextFieldTagModel];
	[self addModelWithText:kTextTitleYear placeHolder:kTextPlaceholderYear tag:VSETextFieldTagYear];
	[self addModelWithText:kTextTitlePlate placeHolder:kTextPlaceholderPlate tag:VSETextFieldTagPlate];
	[self addModelWithText:kTextTitleOdometer placeHolder:kTextPlaceholderOdometer tag:VSETextFieldTagOdometer];
	[self addModelWithText:kTextTitleNickName placeHolder:kTextPlaceholderNickName tag:VSETextFieldTagNickName];
	[self addModelWithText:kTextTitlePrimaryVehicle placeHolder:kTextPlaceholderPrimaryVehicle tag:VSETextFieldTagPrimaryVehicle];
}
- (VSVehicleAddFieldModel*)addModelWithText:(NSString*)text placeHolder:(NSString*)placeHolder tag:(NSInteger)tag {
	VSVehicleAddFieldModel* model = [[VSVehicleAddFieldModel alloc] initWithTitle:text placeHolder:placeHolder tag:tag];
	[self.dataSrc addObject:model];
	return model;
}
@end
