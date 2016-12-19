//
//  VSPurposeModel.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface VSPurposeModel : NSObject
@property (nonatomic, readonly) BOOL defaultPurpose;
@property (nonatomic, copy, readonly) NSString* purposeName;
- (instancetype)initWithName:(NSString*)name isdefault:(BOOL)isdefault;
@end
