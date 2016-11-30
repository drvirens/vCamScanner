//
//  VSBranding.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 8/19/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSBranding.h"

#define WHITE_THEME 1

static NSString* const kFontName = @"HelveticaNeue";

static const CGFloat kFontExtraSmall	= 12.f;
static const CGFloat kFontVerySmall		= 16.f;
static const CGFloat kFontSmall			= 16.f;
static const CGFloat kFontMedium		= 16.f;
static const CGFloat kFontRegular		= 16.f;
static const CGFloat kFontLarge			= 16.f;
static const CGFloat kFontVeryLarge		= 40.f;

@implementation VSBranding

+ (UIFont*)extraSmallFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontExtraSmall];
	return fnt;
}
+ (UIFont*)verySmallFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontVerySmall];
	return fnt;
}
+ (UIFont*)smallFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontSmall];
	return fnt;
}
+ (UIFont*)mediumFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontMedium];
	return fnt;
}
+ (UIFont*)regularFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontRegular];
	return fnt;
}
+ (UIFont*)largeFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontLarge];
	return fnt;
}
+ (UIFont*)extraLargeFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontVeryLarge];
	return fnt;
}
+ (UIFont*)giantLikeBowensDick {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontVeryLarge];
	return fnt;
}
	//font
+ (UIFont*)summaryFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontVeryLarge];
	return fnt;
}

+ (UIFont*)actionTitleFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontMedium];
	return fnt;
}

+ (UIFont*)actionSubTitleFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontExtraSmall];
	return fnt;
}

+ (UIFont*)subSmmaryFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontExtraSmall];
	return fnt;
}

+ (UIFont*)addressFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontExtraSmall];
	return fnt;
}

+ (UIFont*)headerTitleFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontSmall];
	return fnt;
}

+ (UIFont*)notifBodyTitleFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontMedium];
	return fnt;
}

+ (UIFont*)notifBodySubTitleFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontSmall];
	return fnt;
}

+ (UIFont*)navBarFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontMedium];
	return fnt;
}

+ (UIFont*)taableViewSectionTitleFont {
	UIFont* fnt = [UIFont fontWithName:kFontName size:kFontVerySmall];
	return fnt;
}

	//color
+ (UIColor*)actionSubTitleTextColor {
	return [UIColor colorWithRed:(13.f/255.f) green:(133.f/255.f) blue:(103.f/255.f) alpha:1.f];
}

+ (UIColor*)rideCellKeyFontColor {
	return [UIColor colorWithRed:(123.f/255.f) green:(123.f/255.f) blue:(123.f/255.f) alpha:1.f];
}

+ (UIColor*)rideCellValueFontColor {
	return [UIColor colorWithRed:(220.f/255.f) green:(0.f/255.f) blue:(23.f/255.f) alpha:1.f];
}

+ (UIColor*)rideCellSourceAddressIconColor {
	return [[self class] vs_lightGrayColor];
}

+ (UIColor*)rideCellActionIconColor {
	return [[self class] themeColor];
}

+ (UIColor*)rideCellDestinationAddressIconColor {
	return [[self class] vs_lightGrayColor];
}

+ (UIColor*)themeColor {
	return [UIColor colorWithRed:(0.f/255.f) green:(209.f/255.f) blue:(159.f/255.f) alpha:1.f];
}

+ (UIColor*)alertYellowColor {
	return [UIColor colorWithRed:(254.f/255.f) green:(98.f/255.f) blue:(6.f/255.f) alpha:1.f];
}

+ (UIColor*)headerTitleColor {
	return [[self class] vs_blackColor];
}

+ (UIColor*)priceLabelColor {
	return [UIColor colorWithRed:(255.f/255.f) green:(88.f/255.f) blue:(91.f/255.f) alpha:1.f];
}

+ (UIColor*)priceLabelBgColor {
	return [UIColor colorWithRed:(255.f/255.f) green:(88.f/255.f) blue:(91.f/255.f) alpha:0.90f];
}

+ (UIColor*)travelBottomBgColor {
	return [[self class] vs_whiteColor];
}
+ (UIColor*)travelBottomTextColor {
	return [[self class] vs_skyBlueColor];
}

+ (UIColor*)notifBodyTitleColor {
	return [[self class] vs_blackColor];
}

+ (UIColor*)notifBodySubTitleColor {
	return [[self class] vs_darkGrayColor];
}

+ (UIColor*)notifBodyInstructionColor {
	return [[self class] vs_veryDarkGrayColor];
}

+ (UIColor*)notifBodyBgColor {
	return [[self class] vs_lightGrayColor];
}

+ (UIColor*)summaryFontColor {
	return [[self class] vs_whiteColor];
}

+ (UIColor*)summarySeperationLineColor {
	return [[self class] vs_lightGrayColor];
}

+ (UIColor*)subSmmaryFontColor {
	return [[self class] vs_whiteColor];
}

+ (UIColor*)navBarColor {
	return [[self class] vs_whiteColor];
}

+ (UIColor*)notificationHeaderViewBGColor {
		//return [[self class] vs_lightGrayColor];
//		return [[self class] vs_whiteColor];
		//return [UIColor darkGrayColor];
	return [VSBranding themeColor];
}

+ (UIColor*)notifBodyLhsIconBgColor {
	return [[self class] vs_darkGrayColor];
}

+ (UIColor*)addressFontColor {
	return [[self class] vs_veryDarkGrayColor];
}

+ (UIColor*)addressTopContainerBgColor {
	return [[self class] vs_whiteColor];
}

+ (UIColor*)timeColor {
	return [[self class] vs_darkGrayColor];
}

+ (UIColor*)actionTitleTextColor {
	return [[self class] themeColor];
}

+ (UIColor*)vs_darkGrayColor {
	return [UIColor colorWithRed:(191.f/255.f) green:(191.f/255.f) blue:(191.f/255.f) alpha:1.f];
}

+ (UIColor*)vs_veryDarkGrayColor {
	return [UIColor colorWithRed:(108.f/255.f) green:(122.f/255.f) blue:(137.f/255.f) alpha:1.f];
}

+ (UIColor*)vs_lightGrayColor {
	return [UIColor colorWithRed:(236.f/255.f) green:(236.f/255.f) blue:(236.f/255.f) alpha:1.f];
}

+ (UIColor*)vs_whiteColor {
	return [UIColor whiteColor];
}

+ (UIColor*)vs_greenColor {
	return [UIColor colorWithRed:(0.f/255.f) green:(179.f/255.f) blue:(126.f/255.f) alpha:1.f];
}

+ (UIColor*)vs_redColor {
	return [UIColor colorWithRed:(220.f/255.f) green:(0.f/255.f) blue:(23.f/255.f) alpha:1.f];
}

+ (UIColor*)vs_blackColor {
	return [UIColor blackColor];
}

+ (UIColor*)vs_skyBlueColor {
	return [UIColor colorWithRed:(45.f/255.f) green:(175.f/255.f) blue:(236.f/255.f) alpha:1.f];
}

+ (void)decorateCancelBtn:(UIBarButtonItem*)cancelBtn {
	UIFont* fnt = VS_FONT_REGULAR;
	UIColor* fgColor = [VSBranding vs_lightGrayColor];
	NSDictionary* barBtnDick = @{NSFontAttributeName:fnt,
								 NSForegroundColorAttributeName:fgColor};
	[cancelBtn setTitleTextAttributes:barBtnDick forState:UIControlStateNormal];
}
+ (void)decorateEnabledBtn:(UIBarButtonItem*)enabledBtn {
	UIFont* fnt = VS_FONT_REGULAR;
	UIColor* fgColor = [VSBranding vs_darkGrayColor];
	NSDictionary* barBtnDick = @{NSFontAttributeName:fnt,
								 NSForegroundColorAttributeName:fgColor};
	[enabledBtn setTitleTextAttributes:barBtnDick forState:UIControlStateNormal];
}
+ (void)decorateDisabledBtn:(UIBarButtonItem*)disabledBtn {
	UIFont* fnt = VS_FONT_REGULAR;
	UIColor* fgColor = [VSBranding themeColor];
	NSDictionary* barBtnDick = @{NSFontAttributeName:fnt,
								 NSForegroundColorAttributeName:fgColor};
	[disabledBtn setTitleTextAttributes:barBtnDick forState:UIControlStateNormal];
}
@end
