//
//  VSVehiclesViewController.m
//  vsMileTracker
//
//  Created by Virendra Shakya on 10/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "VSVehiclesViewController.h"
#import "VSVehicleModel.h"
#import "VSVehicleCell.h"

const static CGFloat kCellHeight = 50.f;
static NSString* const kSegueAddVehicle = @"segueAddVehicle";

@interface VSVehiclesViewController () <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic) NSMutableArray<NSMutableArray*>* dataSrc;
@end

@implementation VSVehiclesViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	[self setupNavigationBar];
	[self setupDataSrc];
}

- (void)setupNavigationBar {
	self.title = @"Vehicles";
	self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(didTapOnAddBtn:)];
}

- (void)didTapOnAddBtn:(id)sender {
	[self performSegueWithIdentifier:kSegueAddVehicle sender:self];
}

#pragma mark - UITableViewDataSource
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return self.dataSrc.count;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	return self.dataSrc[section].count;
}
- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	
	VSVehicleCell* cell = (VSVehicleCell*)[tableView dequeueReusableCellWithIdentifier:[VSVehicleCell reuseID] forIndexPath:indexPath];
	VSVehicleModel* model = self.dataSrc[indexPath.section][indexPath.row];
	[cell configure:model];
	return cell;
}

#pragma mark - UITableViewDelegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return kCellHeight;
}

#pragma mark - segue
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
	if ([kSegueAddVehicle isEqualToString:segue.identifier]) {
		
	}
}

#pragma mark - Data Source
- (void)setupDataSrc {
	self.dataSrc = [NSMutableArray array];
		//test+
		//vehicles
	NSMutableArray<VSVehicleModel*>* vehicles = [NSMutableArray array];
	
	{
	VSVehicleModel* vehicle = [[VSVehicleModel alloc] initWithName:@"Mustang" odometer:@"20567 mi" isdefault:NO];
	[vehicles addObject:vehicle];
	}
	{
	VSVehicleModel* vehicle = [[VSVehicleModel alloc] initWithName:@"Toyota Corolla" odometer:@"134798 mi" isdefault:YES];
	[vehicles addObject:vehicle];
	}
	
	{
	VSVehicleModel* vehicle = [[VSVehicleModel alloc] initWithName:@"Honda" odometer:@"69503 mi" isdefault:NO];
	[vehicles addObject:vehicle];
	}
	{
	VSVehicleModel* vehicle = [[VSVehicleModel alloc] initWithName:@"My old car" odometer:@"948494 mi" isdefault:NO];
	[vehicles addObject:vehicle];
	}
	
	[self.dataSrc addObject:vehicles];
}

@end
