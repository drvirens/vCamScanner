//
//  VSPurposeCell.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSPurposeCell.h"
#import "VSPurposeModel.h"
#import "VSBranding.h"

@interface VSPurposeCell ()
@property (weak, nonatomic) IBOutlet UIImageView *imageViewLhsIcon;
@property (weak, nonatomic) IBOutlet UILabel *labelPurposeName;

@end

@implementation VSPurposeCell

- (void)awakeFromNib {
    [super awakeFromNib];
	
	UIImage* img = [UIImage imageNamed:@"ic_check_white"];
	img = [img imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
	self.imageViewLhsIcon.image = img;
	self.imageViewLhsIcon.tintColor = [VSBranding vs_skyBlueColor];
	
	self.labelPurposeName.font = VS_FONT_MEDIUM;
}

- (void)prepareForReuse {
	self.labelPurposeName.text = nil;
}

+ (NSString*)reuseID {
	return NSStringFromClass([self class]);
}
- (void)configure:(VSPurposeModel*)model {
	self.labelPurposeName.text = model.purposeName;
	self.imageViewLhsIcon.hidden = !model.defaultPurpose;
	
//	if (model.defaultPurpose) {
//		self.labelPurposeName.textColor = [VSBranding vs_skyBlueColor];
//	} else {
		self.labelPurposeName.textColor = [UIColor blackColor];
//	}
}

@end
