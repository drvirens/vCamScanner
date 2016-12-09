//
//  BODocumentModel.h
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NYTPhoto.h"

@interface BODocumentModel : NSObject <NYTPhoto>
@property (nonatomic, copy, readonly) NSString* docImageName;
@property (nonatomic, copy, readonly) NSString* docTitle;
@property (nonatomic, copy, readonly) NSString* docCategoryIconName;
@property (nonatomic, copy, readonly) NSString* docCategoryName;
@property (nonatomic, copy, readonly) NSDate* docDateCreated;

#pragma mark - NYTPhoto
@property (nonatomic) UIImage *image;
@property (nonatomic) NSData *imageData;
@property (nonatomic) UIImage *placeholderImage;
@property (nonatomic) NSAttributedString *attributedCaptionTitle;
@property (nonatomic) NSAttributedString *attributedCaptionSummary;
@property (nonatomic) NSAttributedString *attributedCaptionCredit;


- (instancetype)initWithTitle:(NSString*)title icon:(NSString*)icon date:(NSDate*)date image:(NSString*)image docCategoryName:(NSString*)docCategoryName;

@end
