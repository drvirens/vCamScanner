//
//  BOInfoEntryView.h
//  vsopencvios
//
//  Created by Virendra Shakya on 11/29/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BOInfoEntryView : UIView

@property (weak, nonatomic) IBOutlet UITextField *textFieldTitle;
@property (weak, nonatomic) IBOutlet UIView *seperatorLineView;
@property (weak, nonatomic) IBOutlet UILabel *labelSelectedCategoryName;
@property (weak, nonatomic) IBOutlet UIImageView *imageViewIcon;
@property (weak, nonatomic) IBOutlet UIView *categoryView;

@property (weak, nonatomic) IBOutlet UIView *dragContainerView;
@property (weak, nonatomic) IBOutlet UIView *dragView;
@property (weak, nonatomic) IBOutlet UIView *dragViewSmaller;
@property (weak, nonatomic) IBOutlet UILabel *labelFileSize;

//@property (weak, nonatomic) IBOutlet UIButton *imageViewCloseIcon;
@property (weak, nonatomic) IBOutlet UIImageView *categoryIcon;
@property (weak, nonatomic) IBOutlet UILabel *labelCategoryTItle;
@property (weak, nonatomic) IBOutlet UIImageView *imageViewCloseIcon;

- (void)clearTitle;
- (void)clearCategoryText;
- (void)setupFileSizeLabel;
- (void)decorateCategoryMoreIcon;
- (void)setupMiscGUI:(id<UITextFieldDelegate>)delegate selectorCateogry:(SEL)didSelectCateogry selectorDragView:(SEL)didSelectDragView;
- (void)hide;
- (void)show;
- (void)showCloseIconOnDragger:(BOOL)showCloseButton;
@end
