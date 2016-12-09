//
//  BODocumentTableViewCell.h
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BODocumentModel.h"
#import "BOFacade.h"
@interface BODocumentTableViewCell : UITableViewCell
@property (nonatomic) BOFacade* facade;
+ (NSString*)reuseID;
- (void)configure:(BODocumentModel*)model;
@end
