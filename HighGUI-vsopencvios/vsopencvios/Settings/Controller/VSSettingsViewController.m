//
//  VSSettingsViewController.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSSettingsViewController.h"
#import "VSMoreCell.h"
#import "VSMoreModel.h"
#import "VSSettingsSwitchCell.h"

static const CGFloat kCellHeight = 50.f;
static NSString* const kTitleVehicle = @"Vehicle";
static NSString* const kTitleAddPurpose = @"Add Category";
static NSString* const kSeguePurpose = @"seguePurpose";
static NSString* const kSegueVehicle = @"segueVehicles";

@interface VSSettingsViewController () <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic) NSMutableArray <NSMutableArray*> * dataSrc;
@end

@implementation VSSettingsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	[self addBarButtons];
	[self setupDataSrc];
}

- (void)addBarButtons {
	self.title = @"Settings";
	self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:self action:@selector(didTapOnCancel:)];
	self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(didTapOnDone:)];
}

- (void)didTapOnCancel:(id)sender {
		//XXX should dismiss entire navigationViewController
	[self dismissViewControllerAnimated:self completion:nil];
}
- (void)didTapOnDone:(id)sender {
		//XXX should dismiss entire navigationViewController
	[self dismissViewControllerAnimated:self completion:nil];
}

#pragma mark - UITableViewDataSource
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return self.dataSrc.count;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	NSMutableArray* rows = self.dataSrc[section];
	return rows.count;
}
- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	UITableViewCell* cell = nil;
	if (indexPath.section == 2 && indexPath.row == 0) {
		VSSettingsSwitchCell* c = (VSSettingsSwitchCell*)[tableView dequeueReusableCellWithIdentifier:[VSSettingsSwitchCell reuseID] forIndexPath:indexPath];
		BOOL ison = YES;
		[c configure:ison];
		cell = c;
		return cell;
	}
	VSMoreCell* moreCell = [tableView dequeueReusableCellWithIdentifier:[VSMoreCell reuseID] forIndexPath:indexPath];
	VSMoreModel* m = self.dataSrc[indexPath.section] [indexPath.row];
	[moreCell configure:m];
	cell = moreCell;
	NSAssert(cell != nil, @"cell cant be nil");
	return cell;
}

#pragma mark - UITableViewDelegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return kCellHeight;
}
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return kCellHeight;
}- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	[tableView deselectRowAtIndexPath:indexPath animated:YES];
	VSMoreModel* m = self.dataSrc[indexPath.section] [indexPath.row];
	if ([m.title isEqualToString:kTitleVehicle]) {
		[self performSegueWithIdentifier:kSegueVehicle sender:indexPath];
	} else if ([m.title isEqualToString:kTitleAddPurpose]) {
		[self performSegueWithIdentifier:kSeguePurpose sender:indexPath];
	}
}

#pragma mark - segue
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
	if ([kSegueVehicle isEqualToString:segue.identifier]) {
		
	} else if ([kSeguePurpose isEqualToString:segue.identifier]) {
		
	}
}

#pragma mark - data src
- (void)setupDataSrc {
	self.dataSrc = [NSMutableArray array];
	
		//test+
		//vehicles
//	{
//	NSMutableArray* vehicles = [NSMutableArray array];
//	VSMoreModel* moreModel = [[VSMoreModel alloc] initWithTitle:kTitleVehicle subTitle:@"Toyota Corolla" iconName:@"ic_keyboard_arrow_right_white"];
//	[vehicles addObject:moreModel];
//	[self.dataSrc addObject:vehicles];
//	}
	
		//purpose
	{
	NSMutableArray* purposes = [NSMutableArray array];
	VSMoreModel* purposeModel = [[VSMoreModel alloc] initWithTitle:kTitleAddPurpose subTitle:@"" iconName:@"ic_keyboard_arrow_right_white"];
	[purposes addObject:purposeModel];
	[self.dataSrc addObject:purposes];
	}

		//sign out and auto-drive detect
	{
//	NSMutableArray* app = [NSMutableArray array];
//	
//		//auto drive detect
//	VSMoreModel* autoDriveModel = [[VSMoreModel alloc] initWithTitle:@"Automatic Drive Detect" subTitle:@"" iconName:@"ic_keyboard_arrow_right_white"];
//	[app addObject:autoDriveModel];
//	
//		//signout
//	VSMoreModel* signOutModel = [[VSMoreModel alloc] initWithTitle:@"Sign out" subTitle:@"" iconName:nil];
//	[app addObject:signOutModel];
//
//	
//	[self.dataSrc addObject:app];
	}
	
		//rate me etc
	{
			//feedback
		NSMutableArray* misc = [NSMutableArray array];
		VSMoreModel* feedbackModel = [[VSMoreModel alloc] initWithTitle:@"Send Feedback" subTitle:@"" iconName:@"ic_keyboard_arrow_right_white"];
		[misc addObject:feedbackModel];
		
			//help
		VSMoreModel* helpModel = [[VSMoreModel alloc] initWithTitle:@"Help" subTitle:@"" iconName:@"ic_keyboard_arrow_right_white"];
		[misc addObject:helpModel];
		
			//rate
		VSMoreModel* rateModel = [[VSMoreModel alloc] initWithTitle:@"Rate this app" subTitle:@"" iconName:@"ic_keyboard_arrow_right_white"];
		[misc addObject:rateModel];
		
			//terms & conditions
		VSMoreModel* tacModel = [[VSMoreModel alloc] initWithTitle:@"Terms & Conditions" subTitle:@"" iconName:@"ic_keyboard_arrow_right_white"];
		[misc addObject:tacModel];
		
		[self.dataSrc addObject:misc];
	}
		//test-
}

- (BOOL)prefersStatusBarHidden {
    return NO;
}

@end
