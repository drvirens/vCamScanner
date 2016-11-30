//
//  VSPurposeAddFieldCell.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/23/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSPurposeAddFieldCell.h"
#import "VSTextFieldView.h"

@implementation VSPurposeAddFieldCell

- (void)awakeFromNib {
    [super awakeFromNib];
}
- (void)prepareForReuse {
	[self configure];
}
+ (NSString*)reuseID {
	return NSStringFromClass([self class]);
}
- (void)configure {
	self.textFieldView.labelTitle.text = @"Add custom purpose";
	self.textFieldView.textField.placeholder = @"Enter custom purpose e.g. Lyft Ride";
}
@end
