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
#import "VSBranding.h"
@interface BODocumentTableViewCell ()
@property (weak, nonatomic) IBOutlet BODocumentView *documentView;
@end
@implementation BODocumentTableViewCell
- (void)awakeFromNib {
    [super awakeFromNib];
    //self.maskView.backgroundColor = [UIColor clearColor];
    //self.maskView.alpha = .4f;
    /*
    CAGradientLayer* blackGradient = [BOGradientLayerController greyGradient];
    blackGradient.frame = self.documentView.maskView.bounds;
    [self.documentView.maskView.layer insertSublayer:blackGradient atIndex:0];
    */
    //self.documentView.contentView.alpha = .4f;
}
- (void)prepareForReuse {
    NSLog(@"prepareForReuse is called ");
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
    
    //CAGradientLayer* blackGradient = [BOGradientLayerController greyGradient];
    //blackGradient.frame = self.documentView.maskView.bounds;
    //[self.documentView.maskView.layer insertSublayer:blackGradient atIndex:0];
}
@end
