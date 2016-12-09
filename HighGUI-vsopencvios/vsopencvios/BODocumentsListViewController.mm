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

#import "NYTPhotosViewController.h"

typedef NS_ENUM(NSUInteger, NYTViewControllerPhotoIndex) {
    NYTViewControllerPhotoIndexCustomEverything = 1,
    NYTViewControllerPhotoIndexLongCaption = 2,
    NYTViewControllerPhotoIndexDefaultLoadingSpinner = 3,
    NYTViewControllerPhotoIndexNoReferenceView = 4,
    NYTViewControllerPhotoIndexCustomMaxZoomScale = 5,
    NYTViewControllerPhotoIndexGif = 6,
    NYTViewControllerPhotoCount,
};

static const CGFloat kCellHeight = 140.f;

@interface BODocumentsListViewController () <UITableViewDataSource, UITableViewDelegate, NYTPhotosViewControllerDelegate>
@property (weak, nonatomic) IBOutlet UITableView *tableView;
//@property (nonatomic) NSMutableArray<NSMutableArray*>* dataSrc;
@property (nonatomic, copy) NSArray<BODocumentModel*>* dataSrc;

@property (nonatomic) NSArray *photos;
@end

@implementation BODocumentsListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"Documents";
    
    //self.photos = [[self class] newTestPhotos];
    [self setupGUI];
    [self setupDataSrc];
}

#pragma mark - GUI
- (void)setupGUI {
    //left close button
    UIImage* closeImg = [UIImage imageNamed:@"ic_close_white"];
    closeImg = [closeImg imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:closeImg style:UIBarButtonItemStylePlain target:self action:@selector(didTapOnCloseCateogryButton:)];
    self.navigationItem.leftBarButtonItem.tintColor = [UIColor lightGrayColor];
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
}
- (void)didTapOnCloseCateogryButton:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
    //[self imageButtonTapped:nil];
}
- (void)didTapOnSelectCateogryButton:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - UITableViewDataSource
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.dataSrc.count;
}
- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    BODocumentTableViewCell* cell = (BODocumentTableViewCell*)[tableView dequeueReusableCellWithIdentifier:[BODocumentTableViewCell reuseID]];
    cell.facade = self.facade;
    BODocumentModel* model = self.dataSrc[indexPath.row];
    [cell configure:model];
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
    [self imageButtonTapped:nil];
}

- (void)imageButtonTapped:(id)sender {
    NYTPhotosViewController *photosViewController = [[NYTPhotosViewController alloc] initWithPhotos:self.photos initialPhoto:nil delegate:self];
    [self presentViewController:photosViewController animated:YES completion:nil];
//    [self updateImagesOnPhotosViewController:photosViewController afterDelayWithPhotos:self.photos];
}

//// This method simulates previously blank photos loading their images after some time.
//- (void)updateImagesOnPhotosViewController:(NYTPhotosViewController *)photosViewController afterDelayWithPhotos:(NSArray *)photos {
//    CGFloat updateImageDelay = 5.0;
//    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(updateImageDelay * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//        for (NYTExamplePhoto *photo in photos) {
//            if (!photo.image && !photo.imageData) {
//                photo.image = [UIImage imageNamed:@"NYTimesBuilding"];
//                [photosViewController updateImageForPhoto:photo];
//            }
//        }
//    });
//}

#pragma mark - NYTPhotosViewControllerDelegate

- (UIView *)photosViewController:(NYTPhotosViewController *)photosViewController referenceViewForPhoto:(id <NYTPhoto>)photo {
    return nil;
}

- (UIView *)photosViewController:(NYTPhotosViewController *)photosViewController loadingViewForPhoto:(id <NYTPhoto>)photo {
    return nil;
}

- (UIView *)photosViewController:(NYTPhotosViewController *)photosViewController captionViewForPhoto:(id <NYTPhoto>)photo {
    return nil;
}

- (CGFloat)photosViewController:(NYTPhotosViewController *)photosViewController maximumZoomScaleForPhoto:(id <NYTPhoto>)photo {
    return 10.0f;
}

- (NSDictionary *)photosViewController:(NYTPhotosViewController *)photosViewController overlayTitleTextAttributesForPhoto:(id <NYTPhoto>)photo {
    return @{NSForegroundColorAttributeName: [UIColor grayColor]};
}

- (NSString *)photosViewController:(NYTPhotosViewController *)photosViewController titleForPhoto:(id<NYTPhoto>)photo atIndex:(NSUInteger)photoIndex totalPhotoCount:(NSUInteger)totalPhotoCount {
    return [NSString stringWithFormat:@"%lu/%lu", (unsigned long)photoIndex+1, (unsigned long)totalPhotoCount];
}

- (void)photosViewController:(NYTPhotosViewController *)photosViewController didNavigateToPhoto:(id <NYTPhoto>)photo atIndex:(NSUInteger)photoIndex {
    NSLog(@"Did Navigate To Photo: %@ identifier: %lu", photo, (unsigned long)photoIndex);
}

- (void)photosViewController:(NYTPhotosViewController *)photosViewController actionCompletedWithActivityType:(NSString *)activityType {
    NSLog(@"Action Completed With Activity Type: %@", activityType);
}

- (void)photosViewControllerDidDismiss:(NYTPhotosViewController *)photosViewController {
    NSLog(@"Did Dismiss Photo Viewer: %@", photosViewController);
}

//test-

#pragma mark - Data Src
- (void)setupDataSrc {
    [self.facade getAllDocuments:^(NSMutableArray* array) {
        self.dataSrc = [NSArray arrayWithArray:array];
        self.photos = self.dataSrc;
        
        [self.tableView reloadData];
    }];
}
@end
