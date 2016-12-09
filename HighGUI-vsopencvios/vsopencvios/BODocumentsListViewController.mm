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

//test+
#import "NYTPhotosViewController.h"
#import "NYTExamplePhoto.h"
//test-

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
@property (nonatomic) NSMutableArray<BODocumentModel*>* dataSrc;

@property (nonatomic) NSArray *photos;
@end

@implementation BODocumentsListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"Documents";
    
    self.photos = [[self class] newTestPhotos];
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
    return self.dataSrc.count;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSInteger ret = self.dataSrc.count;
    return ret;
}
- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    BODocumentTableViewCell* cell = (BODocumentTableViewCell*)[tableView dequeueReusableCellWithIdentifier:[BODocumentTableViewCell reuseID]];
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


//test+
- (void)imageButtonTapped:(id)sender {
//    self.photos = [[self class] newTestPhotos];
    
    NYTPhotosViewController *photosViewController = [[NYTPhotosViewController alloc] initWithPhotos:self.photos initialPhoto:nil delegate:self];
    
    [self presentViewController:photosViewController animated:YES completion:nil];
    
    [self updateImagesOnPhotosViewController:photosViewController afterDelayWithPhotos:self.photos];
}

// This method simulates previously blank photos loading their images after some time.
- (void)updateImagesOnPhotosViewController:(NYTPhotosViewController *)photosViewController afterDelayWithPhotos:(NSArray *)photos {
    CGFloat updateImageDelay = 5.0;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(updateImageDelay * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        for (NYTExamplePhoto *photo in photos) {
            if (!photo.image && !photo.imageData) {
                photo.image = [UIImage imageNamed:@"NYTimesBuilding"];
                [photosViewController updateImageForPhoto:photo];
            }
        }
    });
}

+ (NSArray *)newTestPhotos {
    NSMutableArray *photos = [NSMutableArray array];
    
    for (NSUInteger i = 0; i < NYTViewControllerPhotoCount; i++) {
        NYTExamplePhoto *photo = [[NYTExamplePhoto alloc] init];
        
        if (i == NYTViewControllerPhotoIndexGif) {
            photo.imageData = [NSData dataWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"giphy" ofType:@"gif"]];
        } else if (i == NYTViewControllerPhotoIndexCustomEverything || i == NYTViewControllerPhotoIndexDefaultLoadingSpinner) {
            // no-op, left here for clarity:
            photo.image = nil;
        } else {
            photo.image = [UIImage imageNamed:@"doc1.jpg"];
        }
        
        if (i == NYTViewControllerPhotoIndexCustomEverything) {
            photo.placeholderImage = [UIImage imageNamed:@"doc2.jpg"];
        }
        
        NSString *caption = @"summary";
        switch ((NYTViewControllerPhotoIndex)i) {
            case NYTViewControllerPhotoIndexCustomEverything:
                caption = @"photo with custom everything";
                break;
            case NYTViewControllerPhotoIndexLongCaption:
                caption = @"photo with long caption. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum maximus laoreet vehicula. Maecenas elit quam, pellentesque at tempor vel, tempus non sem. Vestibulum ut aliquam elit. Vivamus rhoncus sapien turpis, at feugiat augue luctus id. Nulla mi urna, viverra sed augue malesuada, bibendum bibendum massa. Cras urna nibh, lacinia vitae feugiat eu, consectetur a tellus. Morbi venenatis nunc sit amet varius pretium. Duis eget sem nec nulla lobortis finibus. Nullam pulvinar gravida est eget tristique. Curabitur faucibus nisl eu diam ullamcorper, at pharetra eros dictum. Suspendisse nibh urna, ultrices a augue a, euismod mattis felis. Ut varius tortor ac efficitur pellentesque. Mauris sit amet rhoncus dolor. Proin vel porttitor mi. Pellentesque lobortis interdum turpis, vitae tincidunt purus vestibulum vel. Phasellus tincidunt vel mi sit amet congue.";
                break;
            case NYTViewControllerPhotoIndexDefaultLoadingSpinner:
                caption = @"photo with loading spinner";
                break;
            case NYTViewControllerPhotoIndexNoReferenceView:
                caption = @"photo without reference view";
                break;
            case NYTViewControllerPhotoIndexCustomMaxZoomScale:
                caption = @"photo with custom maximum zoom scale";
                break;
            case NYTViewControllerPhotoIndexGif:
                caption = @"animated GIF";
                break;
            case NYTViewControllerPhotoCount:
                // this case statement intentionally left blank.
                break;
        }
        
        photo.attributedCaptionTitle = [[NSAttributedString alloc] initWithString:@(i + 1).stringValue attributes:@{NSForegroundColorAttributeName: [UIColor whiteColor], NSFontAttributeName: [UIFont preferredFontForTextStyle:UIFontTextStyleBody]}];
        photo.attributedCaptionSummary = [[NSAttributedString alloc] initWithString:caption attributes:@{NSForegroundColorAttributeName: [UIColor lightGrayColor], NSFontAttributeName: [UIFont preferredFontForTextStyle:UIFontTextStyleBody]}];
        photo.attributedCaptionCredit = [[NSAttributedString alloc] initWithString:@"NYT Building Photo Credit: Nic Lehoux" attributes:@{NSForegroundColorAttributeName: [UIColor grayColor], NSFontAttributeName: [UIFont preferredFontForTextStyle:UIFontTextStyleCaption1]}];
        
        [photos addObject:photo];
    }
    
    return photos;
}

#pragma mark - NYTPhotosViewControllerDelegate

- (UIView *)photosViewController:(NYTPhotosViewController *)photosViewController referenceViewForPhoto:(id <NYTPhoto>)photo {
    if ([photo isEqual:self.photos[NYTViewControllerPhotoIndexNoReferenceView]]) {
        return nil;
    }
    
   // return self.imageButton; //XXX
    return nil;
}

- (UIView *)photosViewController:(NYTPhotosViewController *)photosViewController loadingViewForPhoto:(id <NYTPhoto>)photo {
    if ([photo isEqual:self.photos[NYTViewControllerPhotoIndexCustomEverything]]) {
        UILabel *loadingLabel = [[UILabel alloc] init];
        loadingLabel.text = @"Custom Loading...";
        loadingLabel.textColor = [UIColor greenColor];
        return loadingLabel;
    }
    
    return nil;
}

- (UIView *)photosViewController:(NYTPhotosViewController *)photosViewController captionViewForPhoto:(id <NYTPhoto>)photo {
    if ([photo isEqual:self.photos[NYTViewControllerPhotoIndexCustomEverything]]) {
        UILabel *label = [[UILabel alloc] init];
        label.text = @"Custom Caption View";
        label.textColor = [UIColor whiteColor];
        label.backgroundColor = [UIColor redColor];
        return label;
    }
    
    return nil;
}

- (CGFloat)photosViewController:(NYTPhotosViewController *)photosViewController maximumZoomScaleForPhoto:(id <NYTPhoto>)photo {
    if ([photo isEqual:self.photos[NYTViewControllerPhotoIndexCustomMaxZoomScale]]) {
        return 10.0f;
    }
    
    return 1.0f;
}

- (NSDictionary *)photosViewController:(NYTPhotosViewController *)photosViewController overlayTitleTextAttributesForPhoto:(id <NYTPhoto>)photo {
    if ([photo isEqual:self.photos[NYTViewControllerPhotoIndexCustomEverything]]) {
        return @{NSForegroundColorAttributeName: [UIColor grayColor]};
    }
    
    return nil;
}

- (NSString *)photosViewController:(NYTPhotosViewController *)photosViewController titleForPhoto:(id<NYTPhoto>)photo atIndex:(NSUInteger)photoIndex totalPhotoCount:(NSUInteger)totalPhotoCount {
    if ([photo isEqual:self.photos[NYTViewControllerPhotoIndexCustomEverything]]) {
        return [NSString stringWithFormat:@"%lu/%lu", (unsigned long)photoIndex+1, (unsigned long)totalPhotoCount];
    }
    
    return nil;
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
    self.dataSrc = [NSMutableArray array];
    
    [self.facade getAllDocuments:^(NSMutableArray* array) {
        self.dataSrc = array;
        [self.tableView reloadData];
    }];
    
 
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
    
    //self.dataSrc = scanned;
    //test-
}
@end
