//
//  VSPurposeViewController.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSPurposeViewController.h"
#import "VSPurposeCell.h"
#import "VSPurposeModel.h"
#import "VSAddPurposeViewController.h"

const static CGFloat kCellHeight = 50.f;
static NSString* const kSegueAddPurpose = @"segueAddPurpose";

@interface VSPurposeViewController () <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic) NSMutableArray<NSMutableArray*>* dataSrc;
@end

@implementation VSPurposeViewController
- (void)viewDidLoad {
    [super viewDidLoad];
	[self setupDataSrc];
	[self setupNavigationBar];
}
- (void)setupNavigationBar {
	self.title = @"Purpose";
	self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(didTapOnAddBtn:)];
}
- (void)didTapOnAddBtn:(id)sender {
	[self performSegueWithIdentifier:kSegueAddPurpose sender:self];
}

#pragma mark - UITableViewDataSource
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return self.dataSrc.count;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	return self.dataSrc[section].count;
}
- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	VSPurposeCell* purposeCell = (VSPurposeCell*)[tableView dequeueReusableCellWithIdentifier:[VSPurposeCell reuseID] forIndexPath:indexPath];
	VSPurposeModel* model = self.dataSrc[indexPath.section][indexPath.row];
	[purposeCell configure:model];
	return purposeCell;
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
}

- (void)setupDataSrc {
	self.dataSrc = [NSMutableArray array];
	
		//test+
	NSMutableArray* purposes = [NSMutableArray array];
	[self.dataSrc addObject:purposes];
	
	{
	VSPurposeModel* purpose = [[VSPurposeModel alloc] initWithName:@"Purpose 1" isdefault:NO];
	[purposes addObject:purpose];
	}
	{
	VSPurposeModel* purpose = [[VSPurposeModel alloc] initWithName:@"Purpose 2" isdefault:NO];
	[purposes addObject:purpose];
	}
	{
	VSPurposeModel* purpose = [[VSPurposeModel alloc] initWithName:@"Purpose 3" isdefault:NO];
	[purposes addObject:purpose];
	}
	{
	VSPurposeModel* purpose = [[VSPurposeModel alloc] initWithName:@"Purpose 4" isdefault:YES];
	[purposes addObject:purpose];
	}
	{
	VSPurposeModel* purpose = [[VSPurposeModel alloc] initWithName:@"Purpose 5" isdefault:NO];
	[purposes addObject:purpose];
	}
		//test-
}

@end
