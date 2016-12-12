//
//  BOCategoryModel.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOCategoryModel.h"

//category names
NSString* const kCategoryNameReceipt = @"Receipt";
NSString* const kCategoryNameSchool = @"School";
NSString* const kCategoryNameTravel = @"Travel";
NSString* const kCategoryNameWhiteboard = @"Whiteboard";
NSString* const kCategoryNameEventTicket = @"Event Ticket";
NSString* const kCategoryNameBarcode = @"Barcode";
NSString* const kCategoryNameBusinessCard = @"Business Card";
NSString* const kCategoryNameOther = @"Other";

//icon names
NSString* const kCategoryNameReceiptIcon = @"ic_receipt_white";
NSString* const kCategoryNameSchoolIcon = @"ic_school_white";
NSString* const kCategoryNameTravelIcon = @"ic_card_travel_white";
NSString* const kCategoryNameWhiteboardIcon = @"ic_developer_board_white";
NSString* const kCategoryNameEventTicketIcon = @"ic_event_note_white";
NSString* const kCategoryNameBarcodeIcon = @"ic_code_white";
NSString* const kCategoryNameBusinessCardIcon = @"ic_credit_card_white";
NSString* const kCategoryNameOtherIcon = @"ic_my_location_white";



@interface BOCategoryModel ()
@property (nonatomic, copy, readwrite) NSString* categoryName;
@property (nonatomic, copy, readwrite) NSString* categoryIcon;
@end

@implementation BOCategoryModel
- (instancetype)initWithName:(NSString*)name icon:(NSString*)icon {
    if (self = [super init]) {
        _categoryName = name;
        _categoryIcon = icon;
    }
    return self;
}
@end
