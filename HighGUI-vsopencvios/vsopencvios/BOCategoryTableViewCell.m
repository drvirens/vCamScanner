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

@end

@implementation BOCategoryTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
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
    
    self.labelCategoryName.text = model.categoryName;
    
    self.contentView.backgroundColor = VERY_VERY_LIGHT_GRAY_COLOR;
}

@end
