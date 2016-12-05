//
//  BORecentDocModel.h
//  vsopencvios
//
//  Created by Virendra Shakya on 12/4/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface BORecentDocModel : NSObject
@property (nonatomic, copy, readonly) NSString* docTitle;
@property (nonatomic, copy, readonly) NSString* timeFormatted;
@property (nonatomic, readonly) UIImage* thumbnail;
@property (nonatomic, readonly) NSDate* createdDate; //for sorting

- (instancetype)initWithTitle:(NSString*)docTitle timeFormatted:(NSString*)timeFormatted thumbnail:(UIImage*)thumbnail createdDate:(NSDate*)createdDate;
- (void)computeTime;
@end
