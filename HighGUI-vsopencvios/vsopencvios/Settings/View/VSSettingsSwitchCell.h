//
//  VSSettingsSwitchCell.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/23/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface VSSettingsSwitchCell : UITableViewCell
+ (NSString*)reuseID;
- (void)configure:(BOOL)on;
@end
