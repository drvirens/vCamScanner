//
//  BOCategoryModel.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOCategoryModel.h"

@interface BOCategoryModel ()
@property (nonatomic, copy, readwrite) NSString* categoryName;
@property (nonatomic, copy, readwrite) NSString* categoryIcon;
@end

@implementation BOCategoryModel
- (instancetype)initWithName:(NSString*)name icon:(NSString*)icon {
    if (self = [super init]) {
        _categoryName = name;
        _categoryIcon = icon;
    }
    return self;
}
@end
