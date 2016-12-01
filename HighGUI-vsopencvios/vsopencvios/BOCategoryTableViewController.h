//
//  BOCategoryTableViewController.h
//  vsopencvios
//
//  Created by Virendra Shakya on 11/28/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@class BOCategoryTableViewController;
@protocol BOCategoryTableViewControllerDelegate <NSObject>
- (void)viewController:(BOCategoryTableViewController*)vc didSelectCategory:(NSString*)category;
@end

@interface BOCategoryTableViewController : UITableViewController
@property (nonatomic, weak) id<BOCategoryTableViewControllerDelegate> delegateCategory;
@end
