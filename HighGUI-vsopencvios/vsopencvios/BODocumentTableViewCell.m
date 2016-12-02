//
//  BODocumentTableViewCell.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BODocumentTableViewCell.h"
#import "BODocumentView.h"
#import "BOGradientLayerController.h"

@interface BODocumentTableViewCell ()
@property (weak, nonatomic) IBOutlet BODocumentView *documentView;
@end

@implementation BODocumentTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
//    CAGradientLayer* blackGradient = [BOGradientLayerController blackGradient];
//    blackGradient.frame = self.documentView.containerView.bounds;
//    [self.documentView.containerView.layer insertSublayer:blackGradient atIndex:0];
}
+ (NSString*)reuseID {
    return NSStringFromClass([self class]);
}
- (void)configure:(BODocumentModel*)model {
    UIImage* img = [UIImage imageNamed:model.docImageName];
    self.documentView.imageViewBackground.image = img;
    
    UIImage* icon = [UIImage imageNamed:model.docCategoryIconName];
    self.documentView.containerImageView.image = icon;
    
    self.documentView.containerLabel.text = model.docTitle;
    
    
}
- (void)layoutSubviews {
    [super layoutSubviews];
    CAGradientLayer* blackGradient = [BOGradientLayerController blackGradient];
    blackGradient.frame = self.documentView.containerView.bounds;
    [self.documentView.containerView.layer insertSublayer:blackGradient atIndex:0];
}

@end
