//
//  VSAddPurposeViewController.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/23/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSAddPurposeViewController.h"
#import "VSPurposeAddFieldCell.h"
#import "VSTextFieldView.h"

static const CGFloat kCellHeight = 76.f;

@interface VSAddPurposeViewController () <UITextFieldDelegate>

@end

@implementation VSAddPurposeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
	[self setupNavbaritems];
}

- (void)setupNavbaritems {
	self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:self action:@selector(didTapOnCancelBtn:)];
	self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(didTapOnDoneBtn:)];
	self.navigationItem.rightBarButtonItem.tintColor = [UIColor lightGrayColor];
	self.navigationItem.rightBarButtonItem.enabled = NO;
}
- (void)didTapOnCancelBtn:(id)sender {
	[self dismissViewControllerAnimated:YES completion:nil];
}
- (void)didTapOnDoneBtn:(id)sender {
	[self dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - Table view data source
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 1;
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	VSPurposeAddFieldCell* cell = (VSPurposeAddFieldCell*)[tableView dequeueReusableCellWithIdentifier:[VSPurposeAddFieldCell reuseID] forIndexPath:indexPath];
	cell.textFieldView.textField.delegate = self;
	[cell configure];
	return cell;
}
#pragma mark - UITableViewDelegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return kCellHeight;
}
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return kCellHeight;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	[tableView deselectRowAtIndexPath:indexPath animated:YES];
	
	UITableViewCell* c = [tableView cellForRowAtIndexPath:indexPath];
	if ([c isKindOfClass:[VSPurposeAddFieldCell class]]) {
		VSPurposeAddFieldCell* cell = (VSPurposeAddFieldCell*)c;
		BOOL validated = YES;
		if (indexPath.row %2) {
			validated = NO;
		}
		[cell.textFieldView markValidated:validated];
	}
}
#pragma mark - UITextfieldDelegate
- (BOOL)textFieldShouldReturn:(UITextField *)textField {
	[self validateTextField:textField];
	[self scrollToNextFieldAfterField:textField];
	return YES;
}
- (void)validateTextField:(UITextField*)textField {
		//test+
	VSTextFieldView* tfView = (VSTextFieldView*)textField.superview.superview;
	[tfView markValidated:YES];
		//test-
}
- (void)scrollToNextFieldAfterField:(UITextField*)textField {
	UITableViewCell* currentCell = (UITableViewCell *) textField.superview.superview.superview.superview;
	NSIndexPath* currentIndexPath = [self.tableView indexPathForCell:currentCell];
	NSIndexPath* nextIndexPath = [NSIndexPath indexPathForRow:(currentIndexPath.row + 1) inSection:0];
	if (nextIndexPath.row == 0) {
		UITableViewCell* nextCell = [self.tableView cellForRowAtIndexPath:nextIndexPath];
		[self.tableView scrollToRowAtIndexPath:nextIndexPath atScrollPosition:UITableViewScrollPositionMiddle animated:YES];
		if ([nextCell isKindOfClass:[VSPurposeAddFieldCell class]]) {
			VSPurposeAddFieldCell* c = (VSPurposeAddFieldCell*)nextCell;
			[c.textFieldView.textField becomeFirstResponder];
		}
	}
}


@end
