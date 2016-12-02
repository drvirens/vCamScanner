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

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

+ (NSString*)reuseID {
    return NSStringFromClass([self class]);
}
- (void)configure:(BODocumentModel*)model {
    
}

@end
