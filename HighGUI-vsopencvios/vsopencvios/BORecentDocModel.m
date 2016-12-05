//
//  BORecentDocModel.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/4/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BORecentDocModel.h"

@interface BORecentDocModel ()
@property (nonatomic, copy, readwrite) NSString* docTitle;
@property (nonatomic, copy, readwrite) NSString* timeFormatted;
@property (nonatomic, readwrite) UIImage* thumbnail;
@end

@implementation BORecentDocModel
- (instancetype)initWithTitle:(NSString*)docTitle timeFormatted:(NSString*)timeFormatted thumbnail:(UIImage*)thumbnail createdDate:(NSDate*)createdDate {
    if (self = [super init]) {
        _docTitle = docTitle;
        _timeFormatted = timeFormatted;
        _thumbnail = thumbnail;
        _createdDate = createdDate;
    }
    return self;
}
@end
