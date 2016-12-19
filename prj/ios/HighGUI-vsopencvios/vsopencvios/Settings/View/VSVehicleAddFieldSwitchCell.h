//
//  VSVehicleAddFieldSwitchCell.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/21/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface VSVehicleAddFieldSwitchCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UISwitch *switchView;
@property (weak, nonatomic) IBOutlet UILabel *labelTitle;
+ (NSString*)reuseID;
@end
