//
//  VSVehicleAddFieldCell.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/20/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@class VSTextFieldView;
@class VSVehicleAddFieldModel;
@interface VSVehicleAddFieldCell : UITableViewCell
@property (weak, nonatomic) IBOutlet VSTextFieldView *textFieldView;
+ (NSString*)reuseID;
- (void)configure:(VSVehicleAddFieldModel*)model;
@end
