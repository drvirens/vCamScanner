//
//  BOInfoEntryView.h
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BOInfoEntryView : UIView

@property (weak, nonatomic) IBOutlet UITextField *textFieldTitle;
@property (weak, nonatomic) IBOutlet UIView *seperatorLineView;
@property (weak, nonatomic) IBOutlet UILabel *labelSelectedCategoryName;
@property (weak, nonatomic) IBOutlet UIImageView *imageViewIcon;

@end
