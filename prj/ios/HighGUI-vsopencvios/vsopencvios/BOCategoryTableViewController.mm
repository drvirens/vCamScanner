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
@property (nonatomic) BOCategoryTableViewCell* currSelected;
@property (nonatomic, copy) NSString* selectedCategory;
@end

@implementation BOCategoryTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupDataSource];
    
    self.title = @"Select Category";
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    [self setupGUI];
}
- (void)setupGUI {
    //left bar button
    UIImage* closeImg = [UIImage imageNamed:@"ic_close_white"];
    closeImg = [closeImg imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:closeImg style:UIBarButtonItemStylePlain target:self action:@selector(didTapOnCloseCateogryButton:)];
    self.navigationItem.leftBarButtonItem.tintColor = [UIColor lightGrayColor];
    
    //right bar button
    UIImage* selectImg = [UIImage imageNamed:@"ic_check_white"];
    closeImg = [selectImg imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:selectImg style:UIBarButtonItemStylePlain target:self action:@selector(didTapOnSelectCateogryButton:)];
    self.navigationItem.leftBarButtonItem.tintColor = [UIColor redColor];
    
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
}
- (void)didTapOnCloseCateogryButton:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}
- (void)didTapOnSelectCateogryButton:(id)sender {
    if ([self.delegateCategory respondsToSelector:@selector(viewController:didSelectCategory:)]) {
        [self.delegateCategory viewController:self didSelectCategory:self.selectedCategory];
    }
    [self dismissViewControllerAnimated:YES completion:nil];
}
- (void)setupDataSource {
    self.dataSource = [NSMutableArray array];
    
    BOCategoryModel* model = [[BOCategoryModel alloc] initWithName:kCategoryNameReceipt icon:kCategoryNameReceiptIcon];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:kCategoryNameSchool icon:kCategoryNameSchoolIcon];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:kCategoryNameTravel icon:kCategoryNameTravelIcon];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:kCategoryNameWhiteboard icon:kCategoryNameWhiteboardIcon];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:kCategoryNameEventTicket icon:kCategoryNameEventTicketIcon];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:kCategoryNameBarcode icon:kCategoryNameBarcodeIcon];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:kCategoryNameBusinessCard icon:kCategoryNameBusinessCardIcon];
    [self.dataSource addObject:model];
    
    model = [[BOCategoryModel alloc] initWithName:kCategoryNameOther icon:kCategoryNameOtherIcon];
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
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    if (self.currSelected) {
        [self.currSelected hideIcon];
    }
    BOCategoryTableViewCell* cell = [tableView cellForRowAtIndexPath:indexPath];
    self.currSelected = cell;
    [cell showIcon];
    BOCategoryModel* model = self.dataSource[indexPath.row];
    self.selectedCategory = model.categoryName;
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

@end
