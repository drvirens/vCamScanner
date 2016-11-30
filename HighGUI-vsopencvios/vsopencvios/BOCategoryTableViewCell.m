//
//  BOCategoryTableViewCell.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOCategoryTableViewCell.h"
#import "BOConstants.h"

@interface BOCategoryTableViewCell ()
@property (weak, nonatomic) IBOutlet UIImageView *imageViewIcon;
@property (weak, nonatomic) IBOutlet UILabel *labelCategoryName;
@property (weak, nonatomic) IBOutlet UIImageView *imageviewSelectedIcon;

@end

@implementation BOCategoryTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    self.imageviewSelectedIcon.backgroundColor = SELECTED_FILTER_BACKGROUND_COLOR;
    self.imageviewSelectedIcon.layer.cornerRadius = 12.f;
}

- (void)prepareForReuse {
    self.imageViewIcon.image = nil;
    self.labelCategoryName.text = nil;
}

- (void)configure:(BOCategoryModel*)model {
    UIImage* img = [UIImage imageNamed:model.categoryIcon];
    img = [img imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    self.imageViewIcon.image = img;
    self.imageViewIcon.tintColor = [UIColor redColor];
    
    UIImage* icon = [UIImage imageNamed:@"ic_check_white"];
    self.imageviewSelectedIcon.image = icon;
    self.imageviewSelectedIcon.hidden = YES;
    
    self.labelCategoryName.text = model.categoryName;
    
    self.contentView.backgroundColor = VERY_VERY_LIGHT_GRAY_COLOR;
}

- (void)hideIcon {
    self.imageviewSelectedIcon.hidden = YES;
}
- (void)showIcon {
    self.imageviewSelectedIcon.hidden = NO;
}

@end
