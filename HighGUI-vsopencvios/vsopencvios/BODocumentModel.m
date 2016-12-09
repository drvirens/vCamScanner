//
//  BODocumentModel.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BODocumentModel.h"

@interface BODocumentModel ()
@property (nonatomic, copy, readwrite) NSString* docImageName;
@property (nonatomic, copy, readwrite) NSString* docTitle;
@property (nonatomic, copy, readwrite) NSString* docCategoryIconName;
@property (nonatomic, copy, readwrite) NSString* docCategoryName;
@property (nonatomic, copy, readwrite) NSString* docDateCreated;
@end

@implementation BODocumentModel
- (instancetype)initWithTitle:(NSString*)title icon:(NSString*)icon date:(NSString*)date image:(NSString*)image docCategoryName:(NSString*)docCategoryName {
    if (self = [super init]) {
        _docTitle = title;
        _docCategoryIconName = icon;
        _docDateCreated = date;
        _docImageName = image;
        _docCategoryName = docCategoryName;
        
        [self construct];
    }
    return self;
}

- (void)construct {
    self.placeholderImage = nil;
    NSString *caption = self.docCategoryName;
      
    self.attributedCaptionTitle = [[NSAttributedString alloc] initWithString:self.docTitle attributes:@{NSForegroundColorAttributeName: [UIColor whiteColor], NSFontAttributeName: [UIFont preferredFontForTextStyle:UIFontTextStyleBody]}];
    self.attributedCaptionSummary = [[NSAttributedString alloc] initWithString:caption attributes:@{NSForegroundColorAttributeName: [UIColor lightGrayColor], NSFontAttributeName: [UIFont preferredFontForTextStyle:UIFontTextStyleBody]}];
    self.attributedCaptionCredit = [[NSAttributedString alloc] initWithString:self.docDateCreated attributes:@{NSForegroundColorAttributeName: [UIColor grayColor], NSFontAttributeName: [UIFont preferredFontForTextStyle:UIFontTextStyleCaption1]}];
}

@end
