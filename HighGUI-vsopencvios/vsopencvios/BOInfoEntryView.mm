//
//  BOInfoEntryView.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOInfoEntryView.h"
#import "VSBranding.h"

@interface BOInfoEntryView ()
@property (nonatomic) BOInfoEntryView* weakView;
@end

@implementation BOInfoEntryView

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    if (self = [super initWithCoder:aDecoder]) {
        [self commonInit];
    }
    return self;
}

- (void)commonInit {
    NSString* nibnamed = NSStringFromClass([self class]);
    self.weakView = (BOInfoEntryView*)[[[NSBundle mainBundle] loadNibNamed:nibnamed owner:self options:nil] firstObject];
    [self addSubview:self.weakView];
    self.weakView.frame = self.bounds;
}

- (void)clearTitle {
    //placeholder
    NSDictionary* placeholderTextColor = @{
                                           NSForegroundColorAttributeName : [VSBranding vs_veryVeryDarkGrayColor],
                                           NSFontAttributeName : VS_FONT_VERYSMALL
                                           };
    NSAttributedString* placeHolder = [[NSAttributedString alloc] initWithString:@"ENTER TITLE" attributes:placeholderTextColor];
    self.textFieldTitle.attributedPlaceholder = placeHolder;
    
    //typed text
    self.textFieldTitle.font = VS_FONT_REGULAR;
    self.textFieldTitle.textColor = [UIColor darkGrayColor];
    self.textFieldTitle.text = nil;
}
- (void)clearCategoryText {
    //category label
    NSDictionary* labelCategory = @{
                                    NSForegroundColorAttributeName : [VSBranding vs_veryVeryDarkGrayColor],
                                    NSFontAttributeName : VS_FONT_VERYSMALL
                                    };
    NSAttributedString* category = [[NSAttributedString alloc] initWithString:@"SELECT CATEGORY" attributes:labelCategory];
    self.labelSelectedCategoryName.attributedText = category;
}

- (void)setupFileSizeLabel {
    self.labelFileSize.textColor = [VSBranding vs_brandRedColor];
    self.labelFileSize.font = VS_FONT_EXTRASMALL;
    self.labelFileSize.alpha = 0.5f;
}
- (void)decorateCategoryMoreIcon {
    UIImage* rightArrow = [UIImage imageNamed:@"ic_keyboard_arrow_right_white"];
    rightArrow = [rightArrow imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    self.imageViewIcon.image = rightArrow;
    self.imageViewIcon.tintColor = [VSBranding vs_brandRedColor];
}
- (void)setupMiscGUI:(id<UITextFieldDelegate>)delegate selectorCateogry:(SEL)didSelectCateogry selectorDragView:(SEL)didSelectDragView {
    self.textFieldTitle.delegate = delegate;
    
    //category view tap detect
    self.categoryView.userInteractionEnabled = YES;
    UITapGestureRecognizer* singleTapCategoryView = [[UITapGestureRecognizer alloc] initWithTarget:delegate action:didSelectCateogry];
    singleTapCategoryView.numberOfTapsRequired = 1;
    [self.categoryView addGestureRecognizer:singleTapCategoryView];
    
    //drag view
    self.dragView.layer.cornerRadius = 2.5f;
    self.dragViewSmaller.layer.cornerRadius = 2.f;
    //drag container tap event (Phase 2 = Pan gesture)
    UITapGestureRecognizer* singleTapDragView = [[UITapGestureRecognizer alloc] initWithTarget:delegate action:didSelectDragView];
    singleTapDragView.numberOfTapsRequired = 1;
    [self.dragContainerView addGestureRecognizer:singleTapDragView];
}

@end
