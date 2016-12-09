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
}
- (void)prepareForReuse {
    NSLog(@"prepareForReuse is called ");
}
+ (NSString*)reuseID {
    return NSStringFromClass([self class]);
}
- (void)configure:(BODocumentModel*)model {
    NSURL* url = [self.facade urlForPhotoStorage];
    NSString* u = [url absoluteString];
//    NSString* p = [u stringByAppendingPathComponent:model.docImageName];
    
    NSString* finalpath = [NSString stringWithFormat:@"%@%@", u, model.docImageName];
    
    UIImage* img = [UIImage imageWithContentsOfFile:finalpath];
    self.documentView.imageViewBackground.image = img;
    UIImage* icon = [UIImage imageNamed:model.docCategoryIconName];
    self.documentView.containerImageView.image = icon;
    self.documentView.containerLabel.text = model.docTitle;
}
@end
