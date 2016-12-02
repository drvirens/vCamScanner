//
//  BODocumentTableViewCell.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BODocumentTableViewCell.h"
#import "BODocumentView.h"

@interface BODocumentTableViewCell ()
@property (weak, nonatomic) IBOutlet BODocumentView *documentView;
@end

@implementation BODocumentTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
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

@end
