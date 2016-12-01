//
//  BOCategoryModel.h
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BOCategoryModel : NSObject
@property (nonatomic, copy, readonly) NSString* categoryName;
@property (nonatomic, copy, readonly) NSString* categoryIcon;

- (instancetype)initWithName:(NSString*)name icon:(NSString*)icon;
@end
