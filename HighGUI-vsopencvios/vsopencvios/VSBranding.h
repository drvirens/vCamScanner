//
//  VSBranding.h
//  vsMileTracker
//
//  Created by Virendra Shakya on 8/19/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define VS_FONT_EXTRASMALL			[VSBranding extraSmallFont]
#define VS_FONT_VERYSMALL			[VSBranding verySmallFont]
#define VS_FONT_SMALL				[VSBranding smallFont]
#define VS_FONT_MEDIUM				[VSBranding mediumFont]
#define VS_FONT_REGULAR				[VSBranding regularFont]
#define VS_FONT_LARGE				[VSBranding largeFont]
#define VS_FONT_EXTRALARGE			[VSBranding extraLargeFont]
#define VS_FONT_GIANTLIKEBOWENSDIC	[VSBranding giantLikeBowensDick]

@interface VSBranding : NSObject

	//color - summary
+ (UIColor*)themeColor;
+ (UIColor*)summaryFontColor;
+ (UIColor*)subSmmaryFontColor;
+ (UIColor*)summarySeperationLineColor;
+ (UIColor*)addressFontColor;
+ (UIColor*)addressTopContainerBgColor;
+ (UIColor*)actionTitleTextColor;
+ (UIColor*)timeColor;
+ (UIColor*)rideCellSourceAddressIconColor;
+ (UIColor*)rideCellDestinationAddressIconColor;
+ (UIColor*)rideCellActionIconColor;
+ (UIColor*)vs_whiteColor;

+ (UIFont*)actionSubTitleFont;
+ (UIColor*)actionSubTitleTextColor;
+ (UIColor*)navBarColor;

+ (UIColor*)notificationHeaderViewBGColor;
+ (UIColor*)alertYellowColor;
+ (UIColor*)headerTitleColor;
+ (UIColor*)notifBodyBgColor;
+ (UIColor*)notifBodyLhsIconBgColor;
+ (UIColor*)notifBodyTitleColor;
+ (UIColor*)notifBodySubTitleColor;
+ (UIColor*)notifBodyInstructionColor;
+ (UIColor*)priceLabelColor;
+ (UIColor*)priceLabelBgColor;
+ (UIColor*)travelBottomBgColor;
+ (UIColor*)travelBottomTextColor;
+ (UIColor*)vs_lightGrayColor;
+ (UIColor*)vs_veryDarkGrayColor;
+ (UIColor*)vs_darkGrayColor;
+ (UIColor*)vs_skyBlueColor;
+ (UIColor*)vs_greenColor;
+ (UIColor*)vs_redColor;
+ (UIColor*)vs_brandRedColor;

	//font - summary
	//deprecate+
+ (UIFont*)summaryFont;
+ (UIFont*)subSmmaryFont;
+ (UIFont*)actionTitleFont;
+ (UIFont*)navBarFont;
+ (UIFont*)headerTitleFont;
+ (UIFont*)notifBodyTitleFont;
+ (UIFont*)notifBodySubTitleFont;
+ (UIFont*)taableViewSectionTitleFont;
	//depcreate-
+ (UIFont*)extraSmallFont;
+ (UIFont*)verySmallFont;
+ (UIFont*)smallFont;
+ (UIFont*)mediumFont;
+ (UIFont*)regularFont;
+ (UIFont*)largeFont;
+ (UIFont*)extraLargeFont;
+ (UIFont*)giantLikeBowensDick;


	//ride-cell
	//+ (UIFont*)rideCellValueFont;
+ (UIFont*)addressFont;
+ (UIColor*)rideCellKeyFontColor;
+ (UIColor*)rideCellValueFontColor;

+ (void)decorateCancelBtn:(UIBarButtonItem*)btn;
+ (void)decorateEnabledBtn:(UIBarButtonItem*)enabledBtn;
+ (void)decorateDisabledBtn:(UIBarButtonItem*)disabledBtn;
@end
