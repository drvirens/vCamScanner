//
//  BORecentDocModel.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/4/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BORecentDocModel.h"
#import "NSDate+DateTools.h"

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
        
        [self computeTime];
    }
    return self;
}
- (NSString*)timeAgo:(NSDate*)timeAgoDate {
    //NSDate *timeAgoDate = [NSDate dateWithTimeIntervalSinceNow:-4];
//    NSLog(@"Time Ago: %@", timeAgoDate.timeAgoSinceNow);
//    NSLog(@"Time Ago: %@", timeAgoDate.shortTimeAgoSinceNow);
    //Output:
    //Time Ago: 4 seconds ago
    //Time Ago: 4s
    return timeAgoDate.timeAgoSinceNow;
}
- (void)computeTime {
    NSString* ago = [self timeAgo:_createdDate];
    _timeFormatted = ago;
}
@end
