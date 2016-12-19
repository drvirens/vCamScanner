//
//  VSSettingsSwitchCell.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/23/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSSettingsSwitchCell.h"

@interface VSSettingsSwitchCell ()
@property (weak, nonatomic) IBOutlet UILabel *labelTitle;
@property (weak, nonatomic) IBOutlet UISwitch *switchView;

@end

@implementation VSSettingsSwitchCell
- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}
+ (NSString*)reuseID {
	return NSStringFromClass([self class]);
}
- (void)configure:(BOOL)on {
	
}
@end
