//
//  BOCategoryModel.h
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>

//category names
FOUNDATION_EXPORT NSString* const kCategoryNameReceipt;
FOUNDATION_EXPORT NSString* const kCategoryNameSchool;
FOUNDATION_EXPORT NSString* const kCategoryNameTravel;
FOUNDATION_EXPORT NSString* const kCategoryNameWhiteboard;
FOUNDATION_EXPORT NSString* const kCategoryNameEventTicket;
FOUNDATION_EXPORT NSString* const kCategoryNameBarcode;
FOUNDATION_EXPORT NSString* const kCategoryNameBusinessCard;
FOUNDATION_EXPORT NSString* const kCategoryNameOther;

//icon names
FOUNDATION_EXPORT NSString* const kCategoryNameReceiptIcon;
FOUNDATION_EXPORT NSString* const kCategoryNameSchoolIcon;
FOUNDATION_EXPORT NSString* const kCategoryNameTravelIcon;
FOUNDATION_EXPORT NSString* const kCategoryNameWhiteboardIcon;
FOUNDATION_EXPORT NSString* const kCategoryNameEventTicketIcon;
FOUNDATION_EXPORT NSString* const kCategoryNameBarcodeIcon;
FOUNDATION_EXPORT NSString* const kCategoryNameBusinessCardIcon;
FOUNDATION_EXPORT NSString* const kCategoryNameOtherIcon;




@interface BOCategoryModel : NSObject
@property (nonatomic, copy, readonly) NSString* categoryName;
@property (nonatomic, copy, readonly) NSString* categoryIcon;

- (instancetype)initWithName:(NSString*)name icon:(NSString*)icon;
@end
