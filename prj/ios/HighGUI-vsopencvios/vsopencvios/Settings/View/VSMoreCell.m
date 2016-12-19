//
//  VSMoreCell.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSMoreCell.h"
#import "VSMoreModel.h"
#import "VSBranding.h"

@interface VSMoreCell ()
@property (weak, nonatomic) IBOutlet UILabel *labelTitle;
@property (weak, nonatomic) IBOutlet UILabel *labelSubtitle;
@property (weak, nonatomic) IBOutlet UIImageView *imageViewMoreIcon;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *layoutConstraintImageWidth;
@end

@implementation VSMoreCell
- (void)awakeFromNib {
    [super awakeFromNib];
	self.labelSubtitle.textColor = [VSBranding vs_darkGrayColor];
	self.labelTitle.font = VS_FONT_MEDIUM;
	self.labelSubtitle.font = VS_FONT_MEDIUM;
}

+ (NSString*)reuseID {
	return NSStringFromClass([self class]);
}

- (void)configure:(VSMoreModel*)model {
	self.labelTitle.text = model.title;
	self.labelSubtitle.text = model.subTitle;
	
	if (!model.iconName) {
		self.layoutConstraintImageWidth.constant = 0;
		return;
	}
	UIImage* img = [UIImage imageNamed:model.iconName];
	img = [img imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
	self.imageViewMoreIcon.image = img;
	self.imageViewMoreIcon.tintColor = [UIColor darkGrayColor];
}

@end
