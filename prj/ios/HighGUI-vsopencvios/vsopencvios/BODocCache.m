//
//  BODocCache.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/4/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BODocCache.h"

static const NSInteger kCacheSize = 3;

@interface BOQueue : NSObject
@property(nonatomic, readonly) NSMutableArray* data;
- (void)enqueue:(id)obj;
- (id)dequeue;
- (NSArray*)all;
@end
@interface BOQueue ()
@property(nonatomic, readwrite) NSMutableArray* data;
@end
@implementation BOQueue
- (instancetype)init {
    if (self = [super init]) {
        _data = [NSMutableArray array];
    }
    return self;
}
- (void)enqueue:(id)obj {
    [self.data addObject:obj];
}
- (id)dequeue {
    id ret = [self.data objectAtIndex:0];
    if (ret) {
        [self.data removeObjectAtIndex:0];
    }
    return ret;
}
- (NSArray*)all {
    return [self.data copy];
}
@end

@interface BODocCache ()
@property (nonatomic) BOQueue* queue;
@end

@implementation BODocCache
- (instancetype)init {
    if (self = [super init]) {
        _queue = [[BOQueue alloc] init];
    }
    return self;
}
- (void)addModel:(BORecentDocModel*)model {
    if ([self hasReachedCapacity]) {
        [self evict];
    }
    [self.queue enqueue:model];
}
- (BOOL)hasReachedCapacity {
    return (self.queue.data.count == kCacheSize);
}
- (void)evict {
    id ret = [self.queue dequeue];
    NSLog(@"evicting %@", ret);
}
- (NSArray<BORecentDocModel*>*)all {
    return [self.queue all];
}
@end
