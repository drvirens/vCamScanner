//
//  VSTextFieldView.m
//  VSTextFieldCell
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSTextFieldView.h"
#import "VSBranding.h"

static const CGFloat kImageHeight = 20.f;
static NSString* const kCheckedMark = @"ic_check_white";
static NSString* const kWrongMark = @"ic_close_white";

@interface VSTextFieldView ()
@property (nonatomic, weak) VSTextFieldView* weakSelf;
@property (nonatomic) UIImageView* viewCorrect;
@property (nonatomic) UIImageView* viewIncorrect;
@end

@implementation VSTextFieldView
- (instancetype)initWithCoder:(NSCoder *)aDecoder {
	if ([super initWithCoder:aDecoder]) {
		[self commonInit];
	}
	return self;
}
- (void)commonInit {
	NSString* nib = NSStringFromClass([self class]);
	self.weakSelf = (VSTextFieldView*)[[[NSBundle mainBundle] loadNibNamed:nib owner:self options:nil] firstObject];
	self.weakSelf.frame = self.bounds;
	[self addSubview:self.weakSelf];
	
	[self decorateView];
}
- (void)decorateView {
		//self.textField.rightView = self.viewCorrect;
	self.textField.rightViewMode = UITextFieldViewModeAlways;
	self.labelTitle.font = VS_FONT_MEDIUM;
	self.textField.font = VS_FONT_MEDIUM;
}

- (void)markValidated:(BOOL)isvalid {
	if (isvalid) {
		self.textField.rightView = self.viewCorrect;
	} else {
		self.textField.rightView = self.viewIncorrect;
	}
}

- (void)clear {
	self.textField.rightView = nil;
}

#pragma mark - reusable Elements
- (UIImageView*)viewCorrect {
	if (!_viewCorrect) {
		UIImageView* imgview = [self imageViewWithImage:kCheckedMark bgColor:[VSBranding vs_greenColor]];
		_viewCorrect = imgview;
	}
	return _viewCorrect;
}

- (UIImageView*)viewIncorrect {
	if (!_viewIncorrect) {
		UIImageView* imgview = [self imageViewWithImage:kWrongMark bgColor:[VSBranding vs_redColor]];
		_viewIncorrect = imgview;
	}
	return _viewIncorrect;
}
- (UIImageView*)imageViewWithImage:(NSString*)imgName bgColor:(UIColor*)bgColor {
	CGRect rect = CGRectMake(0, 0, kImageHeight, kImageHeight);
	UIImageView* imgview = [[UIImageView alloc] initWithFrame:rect];
	imgview.contentMode = UIViewContentModeScaleAspectFill;
	
	UIImage* img = [UIImage imageNamed:imgName];
	img = [img imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
	imgview.image = img;
	
	imgview.tintColor = [UIColor whiteColor];
	imgview.backgroundColor = bgColor;
	
	imgview.layer.cornerRadius = kImageHeight/2;
	return imgview;
}

- (void)setTitle:(NSString*)title placeHolder:(NSString*)placeHolder {
	self.labelTitle.text = title;
	self.textField.placeholder = placeHolder;
}

@end
