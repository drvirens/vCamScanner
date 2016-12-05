//
//  BODocCache.h
//  vsopencvios
//
//  Created by Virendra Shakya on 12/4/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "BORecentDocModel.h"

@interface BODocCache : NSObject
- (void)addModel:(BORecentDocModel*)model;
- (NSArray<BORecentDocModel*>*)all;
@end
