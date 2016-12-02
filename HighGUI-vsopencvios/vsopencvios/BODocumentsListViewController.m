//
//  BODocumentsListViewController.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/1/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BODocumentsListViewController.h"
#import "BODocumentView.h"
#import "BODocumentTableViewCell.h"

static const CGFloat kCellHeight = 140.f;

@interface BODocumentsListViewController () <UITableViewDataSource, UITableViewDelegate>
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (nonatomic) NSMutableArray<NSMutableArray*>* dataSrc;
@end

@implementation BODocumentsListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"Documents";
    [self setupGUI];
    [self setupDataSrc];
}

#pragma mark - GUI
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
    [self dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - UITableViewDataSource
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return self.dataSrc.count;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSInteger ret = self.dataSrc[section].count;
    return ret;
}
- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.section == 1) {
        BODocumentTableViewCell* cell = (BODocumentTableViewCell*)[tableView dequeueReusableCellWithIdentifier:[BODocumentTableViewCell reuseID]];
        BODocumentModel* model = self.dataSrc[indexPath.section][indexPath.row];
        [cell configure:model];
        return cell;
    }
    return UITableViewCell.new;
}

#pragma mark - UITableViewDelegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return kCellHeight;
}
- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return kCellHeight;
}


#pragma mark - Data Src
- (void)setupDataSrc {
    self.dataSrc = [NSMutableArray array];
    //test+
    NSMutableArray* recentlyScanned = [NSMutableArray array];
    [recentlyScanned addObject:@"Recently Scanned 1"];
    [recentlyScanned addObject:@"Recently Scanned 2"];
    [recentlyScanned addObject:@"Recently Scanned 3"];
    NSMutableArray* singleRow = [NSMutableArray array];
    [singleRow addObject:recentlyScanned];
    [self.dataSrc addObject:singleRow];
    
    NSMutableArray* scanned = [NSMutableArray array];
    
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    {
        //receipt 1
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc1.jpg"];
        [scanned addObject:model];
        
        //receipt 2
        BODocumentModel* model2 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 2" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc2.jpg"];
        [scanned addObject:model2];
        
        //receipt 3
        BODocumentModel* model3 = [[BODocumentModel alloc] initWithTitle:@"Lunch Receipt 3" icon:@"ic_card_travel_white" date:[NSDate date] image:@"doc3.jpg"];
        [scanned addObject:model3];
    }
    
    [self.dataSrc addObject:scanned];
    //test-
}
@end
