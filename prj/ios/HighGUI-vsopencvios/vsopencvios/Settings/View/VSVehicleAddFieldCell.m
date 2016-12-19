//
//  VSVehicleAddFieldCell.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/20/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSVehicleAddFieldCell.h"
#import "VSTextFieldView.h"
#import "VSVehicleAddFieldModel.h"

@interface VSVehicleAddFieldCell ()

@end

@implementation VSVehicleAddFieldCell
- (void)awakeFromNib {
    [super awakeFromNib];
}
- (void)prepareForReuse {
	
}
+ (NSString*)reuseID {
	return NSStringFromClass([self class]);
}
- (void)configure:(VSVehicleAddFieldModel*)model{
	self.textFieldView.labelTitle.text = model.title;
	self.textFieldView.textField.placeholder = model.placeHolder;
}
@end
