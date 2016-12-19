//
//  VSTextFieldView.h
//  VSTextFieldCell
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface VSTextFieldView : UIView
@property (weak, nonatomic) IBOutlet UILabel *labelTitle;
@property (weak, nonatomic) IBOutlet UITextField *textField;
@property (weak, nonatomic) IBOutlet UIView *viewLine;
- (void)markValidated:(BOOL)isvalid;
- (void)clear;
- (void)setTitle:(NSString*)title placeHolder:(NSString*)placeHolder;
@end
