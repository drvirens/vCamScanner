//
//  VSAddVehicleViewController.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/20/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSAddVehicleViewController.h"
#import "VSVehicleAddFieldModel.h"
#import "VSVehicleAddFieldCell.h"
#import "VSVehicleAddFieldSwitchCell.h"
#import "VSSettingsConstants.h"
#import "VSAddVehicleDataSource.h"
#import "VSTextFieldView.h"

static const CGFloat kCellHeight = 76.f;

@interface VSAddVehicleViewController () <UITableViewDelegate, UITableViewDataSource, UITextFieldDelegate>
@property (nonatomic) VSAddVehicleDataSource* addVehiclesataSrc;
@end

@implementation VSAddVehicleViewController
- (void)viewDidLoad {
    [super viewDidLoad];
	self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
	[self setupDataSrc];
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
- (void)setupDataSrc {
	self.addVehiclesataSrc = [[VSAddVehicleDataSource alloc] init];
}
#pragma mark - UITableViewDataSource
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return 1;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	return self.addVehiclesataSrc.dataSrc.count;
}
- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	VSVehicleAddFieldModel* m = self.addVehiclesataSrc.dataSrc[indexPath.row];
	if (indexPath.row == self.addVehiclesataSrc.dataSrc.count - 1) {
		VSVehicleAddFieldSwitchCell* c = (VSVehicleAddFieldSwitchCell*)[tableView dequeueReusableCellWithIdentifier:[VSVehicleAddFieldSwitchCell reuseID] forIndexPath:indexPath];
		c.switchView.on = NO;
		c.labelTitle.text = m.title;
		return c;
	}
	VSVehicleAddFieldCell* cell = (VSVehicleAddFieldCell*)[tableView dequeueReusableCellWithIdentifier:[VSVehicleAddFieldCell reuseID] forIndexPath:indexPath];
	cell.textFieldView.textField.delegate = self;
	[cell configure:m];
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
	if ([c isKindOfClass:[VSVehicleAddFieldCell class]]) {
		VSVehicleAddFieldCell* cell = (VSVehicleAddFieldCell*)c;
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
	if (nextIndexPath.row < self.addVehiclesataSrc.dataSrc.count) {
		UITableViewCell* nextCell = [self.tableView cellForRowAtIndexPath:nextIndexPath];
		[self.tableView scrollToRowAtIndexPath:nextIndexPath atScrollPosition:UITableViewScrollPositionMiddle animated:YES];
		if ([nextCell isKindOfClass:[VSVehicleAddFieldCell class]]) {
			VSVehicleAddFieldCell* c = (VSVehicleAddFieldCell*)nextCell;
			[c.textFieldView.textField becomeFirstResponder];
		}
	}
}
@end
