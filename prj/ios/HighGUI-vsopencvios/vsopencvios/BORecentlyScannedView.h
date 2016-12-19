//
//  BORecentlyScannedView.h
//  vsopencvios
//
//  Created by Virendra Shakya on 11/30/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@class BORecentlyScannedView;
@protocol BORecentlyScannedViewDelegate <NSObject>
- (void)view:(BORecentlyScannedView*)view didTapCloseButton:(id)sender;
- (void)view:(BORecentlyScannedView*)view didTapOnFirstScannedButton:(id)sender;
- (void)view:(BORecentlyScannedView*)view didTapOnSecondScannedButton:(id)sender;
- (void)view:(BORecentlyScannedView*)view didTapOnThirdScannedView:(id)sender;
@end

@interface BORecentlyScannedView : UIView

@property (nonatomic, weak) id<BORecentlyScannedViewDelegate> delegate;

@property (weak, nonatomic) IBOutlet UIButton *buttonClose;
@property (weak, nonatomic) IBOutlet UIView *containerView;
@property (weak, nonatomic) IBOutlet UIButton *firstScannedView;
@property (weak, nonatomic) IBOutlet UIButton *secondScannedView;
@property (weak, nonatomic) IBOutlet UIButton *thirdScannedView;
@property (weak, nonatomic) IBOutlet UILabel *firstScannedTime;
@property (weak, nonatomic) IBOutlet UILabel *secondScannedTime;
@property (weak, nonatomic) IBOutlet UILabel *thirdScannedTime;

@end
