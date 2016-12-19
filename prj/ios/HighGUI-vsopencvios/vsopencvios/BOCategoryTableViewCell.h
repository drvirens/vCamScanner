//
//  BOCategoryTableViewCell.h
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BOCategoryModel.h"


@interface BOCategoryTableViewCell : UITableViewCell
- (void)configure:(BOCategoryModel*)model;
- (void)hideIcon;
- (void)showIcon;
@end
