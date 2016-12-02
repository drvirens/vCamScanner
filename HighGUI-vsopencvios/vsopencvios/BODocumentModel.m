//
//  BODocumentModel.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BODocumentModel.h"

@interface BODocumentModel ()
@property (nonatomic, copy, readwrite) NSString* docImageName;
@property (nonatomic, copy, readwrite) NSString* docTitle;
@property (nonatomic, copy, readwrite) NSString* docCategoryIconName;
@property (nonatomic, copy, readwrite) NSDate* docDateCreated;
@end

@implementation BODocumentModel
- (instancetype)initWithTitle:(NSString*)title icon:(NSString*)icon date:(NSDate*)date image:(NSString*)image {
    if (self = [super init]) {
        _docTitle = title;
        _docCategoryIconName = icon;
        _docDateCreated = date;
        _docImageName = image;
    }
    return self;
}
@end
