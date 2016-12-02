//
//  BODocumentModel.h
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BODocumentModel : NSObject
@property (nonatomic, copy, readonly) NSString* docTitle;
@property (nonatomic, copy, readonly) NSString* docCategoryIconName;
@property (nonatomic, copy, readonly) NSDate* docDateCreated;

- (instancetype)initWithTitle:(NSString*)title icon:(NSString*)icon date:(NSDate*)date;
@end
