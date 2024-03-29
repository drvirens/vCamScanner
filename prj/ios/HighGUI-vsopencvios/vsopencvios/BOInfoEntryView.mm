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
                                           NSForegroundColorAttributeName : [UIColor darkGrayColor],
                                           NSFontAttributeName : VS_FONT_VERYSMALL
                                           };
    NSAttributedString* placeHolder = [[NSAttributedString alloc] initWithString:@"ENTER TITLE" attributes:placeholderTextColor];
    self.textFieldTitle.attributedPlaceholder = placeHolder;
    
    //typed text
    self.textFieldTitle.font = VS_FONT_REGULAR;
    self.textFieldTitle.textColor = [UIColor whiteColor];
    self.textFieldTitle.text = nil;
}
- (void)clearCategoryText {
    //category label
    NSDictionary* labelCategory = @{
                                    NSForegroundColorAttributeName : [UIColor darkGrayColor],
                                    NSFontAttributeName : VS_FONT_VERYSMALL
                                    };
    NSAttributedString* category = [[NSAttributedString alloc] initWithString:@"SELECT CATEGORY" attributes:labelCategory];
    self.labelSelectedCategoryName.attributedText = category;
}

- (void)setupFileSizeLabel {
    self.labelFileSize.textColor = [VSBranding vs_brandRedColor];
    self.labelFileSize.font = VS_FONT_EXTRASMALL;
    self.labelFileSize.alpha = 0.8f;
    
    //also setup title label
    self.labelCategoryTItle.textColor = [UIColor darkGrayColor];
    self.labelCategoryTItle.font = VS_FONT_MEDIUM;
    
    //and close icon
    [self decorateMiddleCloseIcon];
    
    //and category icon
    [self decorateCategoryIcon];
}
- (void)decorateMiddleCloseIcon {
    UIImage* rightArrow = [UIImage imageNamed:@"ic_close_white"];
    rightArrow = [rightArrow imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    self.imageViewCloseIcon.image = rightArrow;
    self.imageViewCloseIcon.tintColor = [UIColor darkGrayColor];
}
- (void)decorateCategoryMoreIcon {
    UIImage* rightArrow = [UIImage imageNamed:@"ic_keyboard_arrow_right_white"];
    rightArrow = [rightArrow imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    self.imageViewIcon.image = rightArrow;
    self.imageViewIcon.tintColor = [VSBranding vs_brandRedColor];
}
- (void)decorateCategoryIcon {
    UIImage* rightArrow = [UIImage imageNamed:@"ic_event_note_white"];
    rightArrow = [rightArrow imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    self.categoryIcon.image = rightArrow;
    self.categoryIcon.tintColor = [UIColor darkGrayColor];
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
- (void)hideTitle {
    self.labelCategoryTItle.hidden = YES;
    self.categoryIcon.hidden = YES;
}
- (void)showTitle {
    self.labelCategoryTItle.hidden = NO;
    self.categoryIcon.hidden = NO;
}
- (void)hide {
    self.userInteractionEnabled = NO;
    [self showTitle];
    
    [self hideDragView];
}
- (void)show {
    self.userInteractionEnabled = YES;
    [self hideTitle];
    
    [self showDragView];
}
- (void)hideDragView {
    self.dragView.hidden = YES;
    self.dragViewSmaller.hidden = YES;
}
- (void)showDragView {
    self.dragView.hidden = NO;
    self.dragViewSmaller.hidden = NO;
}
- (void)showCloseIconOnDragger:(BOOL)showCloseButton {
    self.imageViewCloseIcon.hidden = !showCloseButton;
    if (showCloseButton) {
        [self hideDragView];
    } else {
        [self showDragView];
    }
}
@end
