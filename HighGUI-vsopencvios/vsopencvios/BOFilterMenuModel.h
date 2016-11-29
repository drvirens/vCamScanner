//
//  BOFilterMenuModel.h
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, BOFilterType) {
    BOFilterTypeOriginal,
    BOFilterTypeBlackWhite,
    BOFilterTypeGray,
    BOFilterTypeMagic
};

@interface BOFilterMenuModel : NSObject
@property (nonatomic, copy, readonly) NSString* menuDisplayName;
@property (nonatomic, readonly) UIImage* menuThumbnail;

- (instancetype)initWithFilterType:(BOFilterType)filterType image:(UIImage*)image;

@end
