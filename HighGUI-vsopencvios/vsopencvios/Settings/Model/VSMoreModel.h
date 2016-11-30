//
//  VSMoreModel.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VSMoreModel : NSObject
@property (nonatomic, copy, readonly) NSString* title;
@property (nonatomic, copy, readonly) NSString* subTitle;
@property (nonatomic, copy, readonly) NSString* iconName;

- (instancetype)initWithTitle:(NSString*)title subTitle:(NSString*)subTitle iconName:(NSString*)iconName;
@end
