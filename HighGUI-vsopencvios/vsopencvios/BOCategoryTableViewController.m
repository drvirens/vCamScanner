//
//  BOCategoryTableViewController.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/28/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOCategoryTableViewController.h"
#import "BOCategoryModel.h"
#import "BOCategoryTableViewCell.h"

@interface BOCategoryTableViewController ()
@property (nonatomic) NSMutableArray* dataSource;
@end

@implementation BOCategoryTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupDataSource];
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
}
- (void)setupDataSource {
    self.dataSource = [NSMutableArray array];
    
    BOCategoryModel* model = [[BOCategoryModel alloc] initWithName:@"Business Receipt" icon:@"ic_receipt_white"];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:@"School" icon:@"ic_school_white"];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:@"Travel" icon:@"ic_card_travel_white"];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:@"Whiteboard" icon:@"ic_developer_board_white"];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:@"Event Tickets" icon:@"ic_event_note_white"];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:@"Barcode" icon:@"ic_code_white"];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:@"Business Card" icon:@"ic_credit_card_white"];
    [self.dataSource addObject:model];
}


#pragma mark - Table view data source
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataSource.count;
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    BOCategoryTableViewCell *cell = (BOCategoryTableViewCell*)[tableView dequeueReusableCellWithIdentifier:@"BOCategoryTableViewCell" forIndexPath:indexPath];
    BOCategoryModel* model = self.dataSource[indexPath.row];
    [cell configure:model];
    return cell;
}
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    return NO;
}

#pragma mark - Table view delegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 60.f;
}
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 60.f;
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

@end
