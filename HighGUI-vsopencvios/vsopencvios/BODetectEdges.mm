//
//  BODetectEdges.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/3/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BODetectEdges.h"
#import "UIImageView+ContentFrame.h"
#import "MMOpenCVHelper.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "vsImageProcessor.hpp"
#include "trace.h"

@interface BODetectEdges ()
@property (nonatomic) NSOperationQueue* operationQueue;
@property (nonatomic) NSOperationQueue* mainQueue;
@property (nonatomic) NSMutableDictionary *sortedPoints;
@end

@implementation BODetectEdges {
    cv::Mat original;
}

- (instancetype)init {
    if (self = [super init]) {
        [self commonInit];
    }
    return self;
}

- (void)commonInit {
    self.operationQueue = [[NSOperationQueue alloc] init];
    self.mainQueue = [NSOperationQueue mainQueue];
}

- (void)dealloc {
    [self operationReleaseResources];
}

#pragma mark - openCV
- (void)apiDetectEdges:(UIImageView*)capturedImageView croppedView:(MMCropView*)croppedView {
    self.croppedView = croppedView;
    
    typeof (self) __weak welf = self;
    //detect edges
    NSBlockOperation* detectEdgesBlock = [NSBlockOperation blockOperationWithBlock:^{
        typeof (self) __strong strongSelf = welf;
        if (strongSelf) {
            [strongSelf operationDetectEdges:capturedImageView croppedView:croppedView];
        }
    }];
    
    [self.operationQueue addOperation:detectEdgesBlock];
}

- (void)operationDetectEdges:(UIImageView*)capturedImageView croppedView:(MMCropView*)croppedView {
    //
    // -------------------------------------------------------------------------------- operationDetectEdges
    //
//    cv::Mat original = [MMOpenCVHelper cvMatFromUIImage:capturedImageView.image];
    original = [MMOpenCVHelper cvMatFromUIImage:capturedImageView.image];
    CGSize targetSize = capturedImageView.contentSize;
    
    cv::resize(original, original, cvSize(targetSize.width, targetSize.height));
    std::vector<std::vector<cv::Point>>squares;
    std::vector<cv::Point> largest_square;
    
    vsImageProcessor::find_squares(original, squares);
    vsImageProcessor::find_largest_square(squares, largest_square);
    
    if (largest_square.size() == 4) {
        // Manually sorting points, needs major improvement. Sorry.
        NSMutableArray *points = [NSMutableArray array];
        self.sortedPoints = [NSMutableDictionary dictionary];
        
        for (int i = 0; i < 4; i++) {
            NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys:[NSValue valueWithCGPoint:CGPointMake(largest_square[i].x, largest_square[i].y)], @"point" , [NSNumber numberWithInt:(largest_square[i].x + largest_square[i].y)], @"value", nil];
            [points addObject:dict];
        }
        
        int min = [[points valueForKeyPath:@"@min.value"] intValue];
        int max = [[points valueForKeyPath:@"@max.value"] intValue];
        int minIndex = 0;
        int maxIndex = 0;
        int missingIndexOne = 0;
        int missingIndexTwo = 0;
        
        for (int i = 0; i < 4; i++) {
            NSDictionary *dict = [points objectAtIndex:i];
            if ([[dict objectForKey:@"value"] intValue] == min) {
                [self.sortedPoints setObject:[dict objectForKey:@"point"] forKey:@"0"];
                minIndex = i;
                continue;
            }
            if ([[dict objectForKey:@"value"] intValue] == max) {
                [self.sortedPoints setObject:[dict objectForKey:@"point"] forKey:@"2"];
                maxIndex = i;
                continue;
            }
            NSLog(@"MSSSING %i", i);
            missingIndexOne = i;
        }
        
        for (int i = 0; i < 4; i++) {
            if (missingIndexOne != i && minIndex != i && maxIndex != i) {
                missingIndexTwo = i;
            }
        }
        
        if (largest_square[missingIndexOne].x < largest_square[missingIndexTwo].x) {
            //2nd Point Found
            [self.sortedPoints setObject:[[points objectAtIndex:missingIndexOne] objectForKey:@"point"] forKey:@"3"];
            [self.sortedPoints setObject:[[points objectAtIndex:missingIndexTwo] objectForKey:@"point"] forKey:@"1"];
        } else {
            //4rd Point Found
            [self.sortedPoints setObject:[[points objectAtIndex:missingIndexOne] objectForKey:@"point"] forKey:@"1"];
            [self.sortedPoints setObject:[[points objectAtIndex:missingIndexTwo] objectForKey:@"point"] forKey:@"3"];
        }
        
        //main thread
        typeof (self) __weak welf = self;
        NSBlockOperation* updateGUIBlock = [NSBlockOperation blockOperationWithBlock:^{
            typeof (self) __strong strongSelf = welf;
            if (strongSelf) {
                [strongSelf operationSetUpGUI];
            }
        }];
        [self.mainQueue addOperation:updateGUIBlock];
    }
}

- (void)operationSetUpGUI {
    [self.croppedView topLeftCornerToCGPoint:[(NSValue *)[self.sortedPoints objectForKey:@"0"] CGPointValue]];
    [self.croppedView topRightCornerToCGPoint:[(NSValue *)[self.sortedPoints objectForKey:@"1"] CGPointValue]];
    [self.croppedView bottomRightCornerToCGPoint:[(NSValue *)[self.sortedPoints objectForKey:@"2"] CGPointValue]];
    [self.croppedView bottomLeftCornerToCGPoint:[(NSValue *)[self.sortedPoints objectForKey:@"3"] CGPointValue]];
    
    //release resources
    typeof (self) __weak welf = self;
    NSBlockOperation* releaseResourceBlock = [NSBlockOperation blockOperationWithBlock:^{
        typeof (self) __strong strongSelf = welf;
        if (strongSelf) {
            [strongSelf operationReleaseResources];
        }
    }];
    [self.operationQueue addOperation:releaseResourceBlock];

}

- (void)operationReleaseResources {
    original.release();
}


@end
