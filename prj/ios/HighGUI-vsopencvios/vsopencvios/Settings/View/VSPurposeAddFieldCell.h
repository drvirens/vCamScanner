//
//  VSPurposeAddFieldCell.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/23/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>
@class VSTextFieldView;
@interface VSPurposeAddFieldCell : UITableViewCell
@property (weak, nonatomic) IBOutlet VSTextFieldView *textFieldView;
+ (NSString*)reuseID;
- (void)configure;
@end
