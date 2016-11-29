//
//  BOFilterMenuModel.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOFilterMenuModel.h"
#import "MMOpenCVHelper.h"

@interface BOFilterMenuModel ()
@property (nonatomic, copy, readwrite) NSString* menuDisplayName;
@property (nonatomic, readwrite) UIImage* menuThumbnail;
@property (nonatomic) UIImage* originalImage;
@end

@implementation BOFilterMenuModel

- (instancetype)initWithFilterType:(BOFilterType)filterType image:(UIImage*)image {
    if (self = [super init]) {
        _originalImage = image;
        [self commonInit:filterType];
    }
    return self;
}

- (void)commonInit:(BOFilterType)filterType {
    if (filterType == BOFilterTypeOriginal) {
        [self doCreateOriginal];
    } else if (filterType == BOFilterTypeBlackWhite) {
        [self doCreateBlackWhite];
    } else if (filterType == BOFilterTypeGray) {
        [self doCreateGray];
    } else if (filterType == BOFilterTypeMagic) {
        [self doCreateMagic];
    }
}

- (void)doCreateOriginal {
    self.menuDisplayName = @"Original";
    self.menuThumbnail = self.originalImage;
}
- (void)doCreateBlackWhite {
    self.menuDisplayName = @"B/W";
    self.menuThumbnail = [self blackandWhite:self.originalImage];
}
- (void)doCreateGray {
    self.menuDisplayName = @"Gray";
    self.menuThumbnail = [self grayImage:self.originalImage];
}
- (void)doCreateMagic {
    self.menuDisplayName = @"Magic";
    self.menuThumbnail = [self magicColor:self.originalImage];
}

//Image Processing
-(UIImage *)grayImage:(UIImage *)processedImage{
    cv::Mat grayImage = [MMOpenCVHelper cvMatGrayFromAdjustedUIImage:processedImage];
    
    cv::GaussianBlur(grayImage, grayImage, cvSize(11,11), 0);
    cv::adaptiveThreshold(grayImage, grayImage, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 5, 2);
    
    UIImage *grayeditImage=[MMOpenCVHelper UIImageFromCVMat:grayImage];
    grayImage.release();
    
    return grayeditImage;
}

-(UIImage *)magicColor:(UIImage *)processedImage{
    cv::Mat  original = [MMOpenCVHelper cvMatFromAdjustedUIImage:processedImage];
    
    cv::Mat new_image = cv::Mat::zeros( original.size(), original.type() );
    
    original.convertTo(new_image, -1, 1.9, -80);
    
    original.release();
    UIImage *magicColorImage=[MMOpenCVHelper UIImageFromCVMat:new_image];
    new_image.release();
    return magicColorImage;
}

-(UIImage *)blackandWhite:(UIImage *)processedImage{
    cv::Mat original = [MMOpenCVHelper cvMatGrayFromAdjustedUIImage:processedImage];
    
    cv::Mat new_image = cv::Mat::zeros( original.size(), original.type() );
    
    original.convertTo(new_image, -1, 1.4, -50);
    original.release();
    
    UIImage *blackWhiteImage=[MMOpenCVHelper UIImageFromCVMat:new_image];
    new_image.release();
    
    return blackWhiteImage;
}


@end
