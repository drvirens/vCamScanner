//
//  VSVehicleCell.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSVehicleCell.h"
#import "VSVehicleModel.h"
#import "VSBranding.h"

@interface VSVehicleCell ()
@property (weak, nonatomic) IBOutlet UIImageView *imageViewRhsIcon;
@property (weak, nonatomic) IBOutlet UILabel *labelVehicleName;
@property (weak, nonatomic) IBOutlet UILabel *labelOdometerReadings;
@end

@implementation VSVehicleCell

- (void)awakeFromNib {
    [super awakeFromNib];
	
	UIImage* img = [UIImage imageNamed:@"ic_check_white"];
	img = [img imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
	self.imageViewRhsIcon.image = img;
	self.imageViewRhsIcon.tintColor = [VSBranding vs_skyBlueColor];
	
	self.labelVehicleName.font = VS_FONT_MEDIUM;
	self.labelOdometerReadings.font = VS_FONT_MEDIUM;
}

- (void)prepareForReuse {
	self.labelVehicleName.text = nil;
	self.labelOdometerReadings.text = nil;
}

+ (NSString*)reuseID {
	return NSStringFromClass([self class]);
}
- (void)configure:(VSVehicleModel*)model{
	self.labelVehicleName.text = model.vehicleName;
	self.labelOdometerReadings.text = model.vehicleOdometerReadings;
	self.imageViewRhsIcon.hidden = !model.defaultVehicle;
	
//	if (model.defaultVehicle) {
//		self.labelVehicleName.textColor = [VSBranding vs_skyBlueColor];
//		self.labelOdometerReadings.textColor = [VSBranding vs_skyBlueColor];
//	} else {
		self.labelVehicleName.textColor = [UIColor blackColor];
		self.labelOdometerReadings.textColor = [VSBranding vs_darkGrayColor];
//	}
}

@end
