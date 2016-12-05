//
//  BOCameraCaptureViewController.m
//  Bowen Swift
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "vsImageProcessor.hpp"
#include "trace.h"

#import "BOCameraCaptureViewController.h"
#import "BOCameraController.h"
#import "MMCropView.h"
#import "UIImageView+ContentFrame.h"
#import "MMOpenCVHelper.h"
#import "BOConstants.h"
#import "BOFiltersView.h"
#import "BOFilterMenuModel.h"
#import "BOInfoEntryView.h"
#import "BOCategoryTableViewController.h"
#import "VSSettingsViewController.h"
#import "VSCameraPermissionsViewController.h"
#import "VSBranding.h"
#import "BORecentlyScannedView.h"
#import "BODocumentsListViewController.h"
#import "BODocCache.h"

typedef enum BOState {
    BONotCroppedState,
    BOCroppedPreviewState,
    BOShareState
} BOState;

static void* gUserLoadContext = &gUserLoadContext;

@interface BOCameraCaptureViewController () <UICollectionViewDelegate, UICollectionViewDataSource, UITextFieldDelegate, BOCategoryTableViewControllerDelegate, VSCameraPermissionsViewControllerDelegate, BORecentlyScannedViewDelegate>
@property (nonatomic) BOCameraController* cameraController;

@property (weak, nonatomic) IBOutlet UIView *cameraView;
@property (weak, nonatomic) IBOutlet UIButton *buttonCameraCapture;
@property (weak, nonatomic) IBOutlet UIButton *buttonFlash;

@property (weak, nonatomic) IBOutlet UIView *cameraViewBottomMenuContainer;

//upper view with imageview inside it
@property (weak, nonatomic) IBOutlet UIView *upperContainerCapturedView;
@property (weak, nonatomic) IBOutlet UIView *containerCapturedView;
@property (weak, nonatomic) IBOutlet UIImageView *capturedImageView;
@property (weak, nonatomic) IBOutlet UIView *lowerContainerCapturedView;

//4 menu buttons
@property (weak, nonatomic) IBOutlet UIButton *menuButtonBack;
@property (weak, nonatomic) IBOutlet UIButton *menuButtonRotateLeft;
@property (weak, nonatomic) IBOutlet UIButton *menuButtonRotateRight;
@property (weak, nonatomic) IBOutlet UIButton *menuButtonSelect;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *activityIndicator;


@property (weak, nonatomic) IBOutlet NSLayoutConstraint *buttonCameraCaptureBottomConstraint;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *lowerContainerCapturedViewBottomLayout;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *marginBetweenFiltersViewAndImageView; //initially it is 200

@property (weak, nonatomic) IBOutlet NSLayoutConstraint *bottomFiltersViewConstraint;
@property (weak, nonatomic) IBOutlet BOFiltersView *filtersMenuView;


@property (weak, nonatomic) IBOutlet NSLayoutConstraint *infoViewTopMarginLayoutConstraint;
@property (weak, nonatomic) IBOutlet BOInfoEntryView *infoEntryView;

@property (weak, nonatomic) IBOutlet UIButton *buttonSettings;
@property (weak, nonatomic) IBOutlet UIButton *buttonShowAllDocuments;

@property (weak, nonatomic) IBOutlet UIView *maskViewRecentlyScanned;
@property (weak, nonatomic) IBOutlet BORecentlyScannedView *viewRecentlyScanned;


@property (nonatomic) BOOL entryInfoPartiallyHidden;
@property (nonatomic) NSMutableArray* dataSource;
@property (nonatomic) UICollectionViewCell* currentlySelectedFilterMenu;


@property (nonatomic) UIImage* image; //original image
@property (nonatomic) UIImage* cropImage;
@property (nonatomic) UIImage* finalProcessedImage;
@property (nonatomic, copy) NSString* categoryName;

@property (strong, nonatomic) MMCropView* croppedView;

@property (nonatomic) BOState state;

//camera permissions
@property (nonatomic, copy) NSString* message;
@property (nonatomic, copy) NSString* positiveBtnTitle;

@property (nonatomic) UIImage* rightImageCheck;
@property (nonatomic) UIImage* rightArrow;
@property (nonatomic) UIImage* rightShareIcon;

//original transform
@property (nonatomic) CATransform3D transformCapturedImageView;
@property (nonatomic) CATransform3D transformCroppedView;

@property (nonatomic) BODocCache* docCache;
@end

@implementation BOCameraCaptureViewController {
    CGFloat _rotateSlider;
    CGRect _initialRect;
    CGRect final_Rect;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.docCache = [[BODocCache alloc] init];
    self.state = BONotCroppedState;
    
    [self setupRightButton];
    
    [self setupRecentlyScannedView];
    [self hideRecentlyScannedView];
    
    [self clearTitle];
    [self clearCategoryText];
    [self setupMiscGUI];
    [self decorateCategoryMoreIcon];
    
    [self setupFitersMenu];
    
	[self setupContainerView];
	[self setupCameraButton];
    
    [self setupDefaultNextActionButton];
    [self decorateSettingsButton];
    [self decorateShowDocumentsButton];
    [self setupFileSizeLabel];
    
    self.transformCapturedImageView = self.capturedImageView.layer.transform;
    self.transformCroppedView = self.croppedView.layer.transform;
    
	[self startCamera];
}
- (void)setupRightButton {
    self.menuButtonSelect.tintColor = [VSBranding vs_brandRedColor];
    
    //cache rightImageCheck
    self.rightImageCheck = [UIImage imageNamed:@"ic_check_white"];
    self.rightImageCheck = [self.rightImageCheck imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    
    self.rightArrow = [UIImage imageNamed:@"ic_arrow_forward_white"];
    self.rightArrow = [self.rightArrow imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    
    self.rightShareIcon = [UIImage imageNamed:@"ic_share_white"];
    self.rightShareIcon = [self.rightShareIcon imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    
    self.activityIndicator.hidden = YES;
}
- (void)setupRecentlyScannedView {
    self.viewRecentlyScanned.delegate = self;
}

#pragma mark - infoEntryView interactions
- (void)setupFileSizeLabel {
    [self.infoEntryView setupFileSizeLabel];
}
- (void)decorateCategoryMoreIcon {
    [self.infoEntryView decorateCategoryMoreIcon];
}
- (void)clearTitle {
    [self.infoEntryView clearTitle];
}
- (void)clearCategoryText {
    [self.infoEntryView clearCategoryText];
}
- (void)setupMiscGUI {
    [self.infoEntryView setupMiscGUI:self selectorCateogry:@selector(didSelectCateogry:) selectorDragView:@selector(didSelectDragView:)];
    
    self.infoEntryView.labelCategoryTItle.text = nil;
    [self.infoEntryView show];
    
    //upper container captured view tap
    UITapGestureRecognizer* upperContainerCapturedViewTapped = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(didTapOnUpperContainerCapturedView:)];
    upperContainerCapturedViewTapped.numberOfTapsRequired = 1;
    [self.upperContainerCapturedView addGestureRecognizer:upperContainerCapturedViewTapped];
}


- (void)decorateSettingsButton {
//    UIImage* settings = [UIImage imageNamed:@"ic_settings_white"];
//    settings = [settings imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
//    [self.buttonSettings setImage:settings forState:UIControlStateNormal];
//    self.buttonSettings.tintColor = [VSBranding vs_brandRedColor];
}
- (void)decorateShowDocumentsButton {
    UIImage* settings = [UIImage imageNamed:@"ic_view_list_white"];
    settings = [settings imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    [self.buttonShowAllDocuments setImage:settings forState:UIControlStateNormal];
    self.buttonShowAllDocuments.tintColor = [VSBranding vs_whiteColor];
}

- (void)setupContainerView {
	self.containerCapturedView.hidden = YES;
}
- (void)setupCameraButton {
	self.buttonCameraCapture.layer.borderColor = [VSBranding vs_brandRedColor].CGColor;
	self.buttonCameraCapture.layer.borderWidth = 2.f;
	self.buttonCameraCapture.layer.cornerRadius = kHeightCapturePhotoButton/2.f;
    
    UIImage* icon = [UIImage imageNamed:@"ic_camera_alt_white"];
    icon = [icon imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    [self.buttonCameraCapture setImage:icon forState:UIControlStateNormal];
    self.buttonCameraCapture.tintColor = [VSBranding vs_brandRedColor];
}

- (void)didSelectCateogry:(id)sender {
    NSLog(@"didSelectCateogry");
    [self performSegueWithIdentifier:@"category" sender:self];
}
- (void)didSelectDragView:(id)sender {
    NSLog(@"didSelectDragView");
    if (self.entryInfoPartiallyHidden) {
        [self showInfoEntryViewPartially];
    } else {
        [self hideInfoEntryViewPartially];
        [self.infoEntryView.textFieldTitle resignFirstResponder];
    }
}
- (void)didTapOnUpperContainerCapturedView:(id)sender {
    NSLog(@"didTapOnUpperContainerCapturedView");
    if (self.state == BOCroppedPreviewState) {
        NSLog(@"if keyboard is being shown hide it");
        [self.infoEntryView.textFieldTitle resignFirstResponder];
    }
}

#pragma mark - action handlers for main landing page in camera preview mode
- (IBAction)didTapSettingsButton:(id)sender {
    UIStoryboard* sb = [UIStoryboard storyboardWithName:@"Settings" bundle:nil];
    VSSettingsViewController* settingsVC = (VSSettingsViewController*)[sb instantiateViewControllerWithIdentifier:@"VSSettingsViewController"];
    UINavigationController* navc = [[UINavigationController alloc] initWithRootViewController:settingsVC];
    [self presentViewController:navc animated:YES completion:nil];
}

- (IBAction)didTapCapturePhoto:(id)sender {
    self.buttonCameraCapture.alpha = 0.35f;
    self.buttonCameraCapture.enabled = NO;
    
    //hide settings button
    //self.buttonSettings.hidden = YES;
    
    [self hideRecentlyScannedView];
    
	typeof (self) __weak welf = self;
	[self.cameraController capturePhotoWithCompletion:^(UIImage * image) {
		NSLog(@"did capture ");
		welf.image = image;
        welf.capturedImageView.image = image;
		[welf showCapturedImageLoading];
        
	}];
}
- (IBAction)didTapOnToggleFlashButton:(id)sender {
    BOOL on = [self.cameraController toggleCameraFlash];
    UIImage* onicon = [UIImage imageNamed:@"ic_flash_on_white"];
    UIImage* officon = [UIImage imageNamed:@"ic_flash_off_white"];
    UIImage* curr = nil;
    if (on) {
        curr = onicon;
    } else {
        curr = officon;
    }
    [self.buttonFlash setImage:curr forState:UIControlStateNormal];
}
- (IBAction)didTapShowAllDocumentsButton:(id)sender {
    NSLog(@"didTapShowAllDocumentsButton");
    [self performSegueWithIdentifier:@"documents" sender:self];
}

#pragma mark - BORecentlyScannedViewDelegate
- (void)view:(BORecentlyScannedView*)view didTapCloseButton:(id)sender {
    [self hideRecentlyScannedView];
}
- (void)view:(BORecentlyScannedView*)view didTapOnFirstScannedButton:(id)sender {
    NSLog(@"didTapOnFirstScannedButton");
}
- (void)view:(BORecentlyScannedView*)view didTapOnSecondScannedButton:(id)sender {
    NSLog(@"didTapOnSecondScannedButton");
}
- (void)view:(BORecentlyScannedView*)view didTapOnThirdScannedView:(id)sender {
    NSLog(@"didTapOnThirdScannedView");
}

#pragma mark -
- (void)detectEdgesOnImageAndDisplay:(UIImage*)image {
    [self prepareCropView];
}

- (void)showCapturedImageLoading {
	typeof (self) __weak welf = self;
	dispatch_async(dispatch_get_main_queue(), ^{
		typeof (self) __strong strongSelf = welf;
		if (strongSelf) {
			[strongSelf doShowCapturedImage];
		}
	});
}
- (void)doShowCapturedImage {
    [self hideCameraOverlay];
}

- (void)populateRecentlyScannedView {
    NSArray<BORecentDocModel*>* recentlyScannedDocs = [self.docCache all];
    [recentlyScannedDocs enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        BORecentDocModel* m = (BORecentDocModel*)obj;
        UIButton* btn = nil;
        UILabel* label = nil;
        if (idx == 0) {
            btn = self.viewRecentlyScanned.firstScannedView;
            label = self.viewRecentlyScanned.firstScannedTime;
        } else if (idx == 1) {
            btn = self.viewRecentlyScanned.secondScannedView;
            label = self.viewRecentlyScanned.secondScannedTime;
        } else if (idx == 2) {
            btn = self.viewRecentlyScanned.thirdScannedView;
            label = self.viewRecentlyScanned.thirdScannedTime;
        }
        [btn setBackgroundImage:nil forState:UIControlStateNormal];
        [btn setImage:nil forState:UIControlStateNormal];
        btn.backgroundColor = [UIColor clearColor];
        [btn setImage:m.thumbnail forState:UIControlStateNormal];
        label.text = @"dan's dick";// m.timeFormatted;
    }];
}

#pragma mark - hide/show
- (void)hideRecentlyScannedView {
    self.maskViewRecentlyScanned.hidden = YES;
    self.viewRecentlyScanned.hidden = YES;
}
- (void)showRecentlyScannedView {
    self.maskViewRecentlyScanned.hidden = NO;
    self.viewRecentlyScanned.hidden = NO;
    
    [self populateRecentlyScannedView];
}
- (void)hideCameraOverlay {
    [self.view layoutIfNeeded];
    self.buttonCameraCaptureBottomConstraint.constant = -(kHeightLowerView);
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
    [self showBottomMenu];
}
- (void)showCameraOverlay {
    [self.view layoutIfNeeded];
    self.buttonCameraCaptureBottomConstraint.constant = 0;
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
}
- (void)hideBottomMenu {
    [self.containerCapturedView layoutIfNeeded];
    self.lowerContainerCapturedViewBottomLayout.constant = -(kHeightLowerView);
    [UIView animateWithDuration:.25 animations:^{
        [self.containerCapturedView layoutIfNeeded];
    }];
}
- (void)showBottomMenu {
    [self.containerCapturedView layoutIfNeeded];
    self.lowerContainerCapturedViewBottomLayout.constant = (0);
    [UIView animateWithDuration:.25 animations:^{
        [self.containerCapturedView layoutIfNeeded];
    }];
    
    self.containerCapturedView.hidden = NO;
    self.cameraView.hidden = YES;
    
    self.buttonCameraCapture.alpha = 1.f;
    self.buttonCameraCapture.enabled = YES;
    
    [self detectEdgesOnImageAndDisplay:self.image];
}
- (void)hideInfoEntryView {
    [self.view layoutIfNeeded];
    self.infoViewTopMarginLayoutConstraint.constant = -(kTopMarginEntryView);
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
    [self showCloseIconOnDragger:NO];
}
- (void)showInfoEntryView {
    [self.view layoutIfNeeded];
    self.infoViewTopMarginLayoutConstraint.constant = 0;
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
    [self showCloseIconOnDragger:YES];
}
- (void)hideInfoEntryViewPartially {
    [self.view layoutIfNeeded];
    self.infoViewTopMarginLayoutConstraint.constant = -(kTopMarginEntryView - 40);
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
    self.entryInfoPartiallyHidden = YES;
    [self showCloseIconOnDragger:NO];
}
- (void)showInfoEntryViewPartially {
    [self.view layoutIfNeeded];
    self.infoViewTopMarginLayoutConstraint.constant = 0;
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
    self.entryInfoPartiallyHidden = NO;
    [self showCloseIconOnDragger:YES];
}
- (void)hideInfoEntryViewPartiallyAndDisableDragger {
    [self.view layoutIfNeeded];
    self.infoViewTopMarginLayoutConstraint.constant = -(kTopMarginEntryView - 40);
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
    self.entryInfoPartiallyHidden = NO;
    [self.infoEntryView hide];
    self.infoEntryView.imageViewCloseIcon.hidden = YES;
}
- (void)showCloseIconOnDragger:(BOOL)showCloseButton {
    [self.infoEntryView showCloseIconOnDragger:showCloseButton];
}


- (void)hideFiltersView {
    [self.view layoutIfNeeded];
    self.bottomFiltersViewConstraint.constant = -(kFiltersViewBottomMargin + kHeightLowerView);
    self.marginBetweenFiltersViewAndImageView.constant = kMarginBetweenFiltersViewAndImageView;
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
}
- (void)showFiltersView {
    [self.view layoutIfNeeded];
    self.bottomFiltersViewConstraint.constant = kHeightLowerView;
    self.marginBetweenFiltersViewAndImageView.constant = 0.f;
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
}
- (void)setupFitersMenu {
    UINib* nib = [UINib nibWithNibName:@"BOFilterCell" bundle:nil];
    [self.filtersMenuView.collectionView registerNib:nib forCellWithReuseIdentifier:@"BOFilterCell"];
    
    self.filtersMenuView.collectionView.delegate = self;
    self.filtersMenuView.collectionView.dataSource = self;
    
    self.dataSource = [NSMutableArray array];
}
- (void)populateFiltersMenu {
    [self.dataSource removeAllObjects];
    //XXX - do on background thread
    BOFilterMenuModel* original = [[BOFilterMenuModel alloc] initWithFilterType:BOFilterTypeOriginal image:self.cropImage];
    BOFilterMenuModel* bw = [[BOFilterMenuModel alloc] initWithFilterType:BOFilterTypeBlackWhite image:self.cropImage];
    BOFilterMenuModel* gray = [[BOFilterMenuModel alloc] initWithFilterType:BOFilterTypeGray image:self.cropImage];
    BOFilterMenuModel* magic = [[BOFilterMenuModel alloc] initWithFilterType:BOFilterTypeMagic image:self.cropImage];
    
    [self.dataSource addObject:original];
    [self.dataSource addObject:bw];
    [self.dataSource addObject:gray];
    [self.dataSource addObject:magic];

    [self.filtersMenuView.collectionView reloadData];
}
#pragma mark - UICollectionViewDelegate
- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.dataSource.count;
}
- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    UICollectionViewCell* cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"BOFilterCell" forIndexPath:indexPath];
    
    cell.layer.borderColor = [VSBranding vs_veryDarkGrayColor].CGColor;
    cell.layer.borderWidth = .5f;
    cell.layer.cornerRadius = 0.f;
    
    UILabel* label = (UILabel*)[cell viewWithTag:100];
    BOFilterMenuModel* filter = self.dataSource[indexPath.item];
    [self decorateCellLabel:label text:filter.menuDisplayName];
    
    UIImageView* imageview = (UIImageView*)[cell viewWithTag:200];
    imageview.image = filter.menuThumbnail;
    
    if (self.currentlySelectedFilterMenu == nil) {
        if (indexPath.item == 0) { //put first cell as selected by default
            self.currentlySelectedFilterMenu = cell;
            cell.layer.borderColor = SELECTED_FILTER_BACKGROUND_COLOR.CGColor;
            cell.layer.borderWidth = 2.f;
            cell.layer.cornerRadius = 3.f;
            [self decorateSelectedCellLabel:label text:filter.menuDisplayName];
        }
    }
    
    return cell;
}
- (void)decorateCellLabel:(UILabel*)label text:(NSString*)text {
    //category label
    NSDictionary* labelCategory = @{
                                    NSForegroundColorAttributeName : [UIColor lightGrayColor],
                                    NSFontAttributeName : VS_FONT_EXTRASMALL
                                    };
    NSAttributedString* category = [[NSAttributedString alloc] initWithString:text attributes:labelCategory];
    label.attributedText = category;
}
- (void)decorateSelectedCellLabel:(UILabel*)label text:(NSString*)text {
    //category label
    NSDictionary* labelCategory = @{
                                    NSForegroundColorAttributeName : [UIColor whiteColor],
                                    NSFontAttributeName : VS_FONT_EXTRASMALL
                                    };
    NSAttributedString* category = [[NSAttributedString alloc] initWithString:text attributes:labelCategory];
    label.attributedText = category;
}

#pragma mark - UICollectionViewDataSource
- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    BOFilterMenuModel* filter = self.dataSource[indexPath.item];
    
    //unselect current selection first
    UILabel* label = nil;
    if (self.currentlySelectedFilterMenu) {
        self.currentlySelectedFilterMenu.layer.borderColor = [VSBranding vs_veryDarkGrayColor].CGColor;
        self.currentlySelectedFilterMenu.layer.borderWidth = .5f;
        self.currentlySelectedFilterMenu.layer.cornerRadius = 0.f;
        
        label = (UILabel*)[self.currentlySelectedFilterMenu viewWithTag:100];
        [self decorateCellLabel:label text:label.text];
    }
    
    UICollectionViewCell* cell = [collectionView cellForItemAtIndexPath:indexPath];
    self.currentlySelectedFilterMenu = cell;
    cell.layer.borderColor = SELECTED_FILTER_BACKGROUND_COLOR.CGColor;
    cell.layer.borderWidth = 2.f;
    cell.layer.cornerRadius = 3.f;
    
    label = (UILabel*)[cell viewWithTag:100];
    
    self.capturedImageView.image = filter.menuThumbnail;
    
    [self decorateSelectedCellLabel:label text:label.text];
    
    self.finalProcessedImage = filter.menuThumbnail;
}

#pragma mark - UITextFieldDelegate
- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}
- (void)textFieldDidEndEditing:(UITextField *)textField {
    NSString* capsText = textField.text;
    capsText = [capsText uppercaseString];
    self.infoEntryView.labelCategoryTItle.text = capsText;
}

#pragma mark - 4 menu buttons
- (IBAction)didSelectMenuGoBack:(id)sender {
    [self.activityIndicator stopAnimating];
    
    [self hideBottomMenu];
    [self showCameraOverlay];
    
    self.containerCapturedView.hidden = YES;
    self.cameraView.hidden = NO;
    
    [self.croppedView removeFromSuperview];
    self.croppedView = nil;
    
    self.capturedImageView.layer.transform = self.transformCapturedImageView;
    
    if (self.state == BOShareState) {
        [self showRecentlyScannedView];
    }
    
    [self transitMenuItemsToNotCroppedMode];
    if (self.state == BOCroppedPreviewState) {
        [self hideFiltersView];
        [self hideInfoEntryView];
    }
    self.state = BONotCroppedState;
    
    if (self.currentlySelectedFilterMenu) {
        self.currentlySelectedFilterMenu.layer.borderColor = VERY_VERY_LIGHT_GRAY_COLOR.CGColor;
    }
    self.currentlySelectedFilterMenu = nil;
    
    //self.buttonSettings.hidden = NO;
    [self clearTitle];
    [self clearCategoryText];
    [self.infoEntryView show];
    self.infoEntryView.labelCategoryTItle.text = nil;
    
    self.categoryName = nil;
}
- (IBAction)didSelectMenuRotateLeft:(id)sender {
    CGFloat value = (int)floorf((_rotateSlider + 1)*2) - 1;
    
    if(value>4){ value -= 4; }
    _rotateSlider = value / 2 - 1;
    [UIView animateWithDuration:0.5 animations:^{
        [self rotateStateDidChange];
    }];
}
- (IBAction)didSelectMenuRotateRight:(id)sender {
    CGFloat value = (int)floorf((_rotateSlider + 1)*2) + 1;
    
    if(value>4){ value -= 4; }
    _rotateSlider = value / 2 - 1;
    [UIView animateWithDuration:0.5 animations:^{
        [self rotateStateDidChange];
    }];
}
- (IBAction)didSelectMenuSelect:(id)sender {
            if (self.state == BOCroppedPreviewState) {
                NSLog(@"BOCroppedPreviewState - show share state/view");
                [self putUIInProcessingStart];
                
                [self hideInfoEntryViewPartiallyAndDisableDragger]; //disable drag and remove the dragger - use
                [self hideFiltersView];
                [self transitMenuItemsToShareMode];
                
                [self putUIInProcessingFinished];
                
                [self apiAddDocument]; //this is fire and forget
            } else if (self.state == BOShareState) {
                [self share:self];
            } else {
                [self doCropImage];
            }
}
- (void)setupDefaultNextActionButton {
    [self.menuButtonSelect setImage:self.rightImageCheck forState:UIControlStateNormal];
}
- (void)transitMenuItemsToPreviewMode {
    self.menuButtonRotateLeft.hidden = YES;
    self.menuButtonRotateRight.hidden = YES;
    
    [self.menuButtonSelect setImage:self.rightArrow forState:UIControlStateNormal];
    self.state = BOCroppedPreviewState;
}
- (void)transitMenuItemsToNotCroppedMode {
    self.menuButtonRotateLeft.hidden = NO;
    self.menuButtonRotateRight.hidden = NO;
    
    [self.menuButtonSelect setImage:self.rightImageCheck forState:UIControlStateNormal];
    self.state = BOCroppedPreviewState;
}
- (void)transitMenuItemsToShareMode {
    self.menuButtonRotateLeft.hidden = YES;
    self.menuButtonRotateRight.hidden = YES;

    [self.menuButtonSelect setImage:self.rightShareIcon forState:UIControlStateNormal];
    self.state = BOShareState;
}
- (void)share:(id)sender {
    NSLog(@"---------------------------------- Start of share");
    [self putUIInProcessingStart];
    
    
    UIImage *image = self.finalProcessedImage;
    if (image == nil) {
        image = self.cropImage;
    }
    NSArray *activityItems = @[image];
    UIActivityViewController *activityViewControntroller = [[UIActivityViewController alloc] initWithActivityItems:activityItems applicationActivities:nil];
    activityViewControntroller.excludedActivityTypes = @[];
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        activityViewControntroller.popoverPresentationController.sourceView = self.view;
        activityViewControntroller.popoverPresentationController.sourceRect = CGRectMake(self.view.bounds.size.width/2, self.view.bounds.size.height/4, 0, 0);
    }
    [self presentViewController:activityViewControntroller animated:true completion:^{
        NSLog(@"---------------------------------- END of share");
        [self putUIInProcessingFinished];
    }];
}
#pragma mark - image crop view
- (void)prepareCropView {
    CGRect cropFrame = CGRectMake(self.capturedImageView.contentFrame.origin.x,
                                  self.capturedImageView.contentFrame.origin.y + kImageViewMargin,
                                  self.capturedImageView.contentFrame.size.width,
                                  self.capturedImageView.contentFrame.size.height );
    
    self.croppedView= [[MMCropView alloc] initWithFrame:cropFrame];
    [self.upperContainerCapturedView addSubview:self.croppedView];
    
    UIPanGestureRecognizer *singlePan = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(singlePan:)];
    singlePan.maximumNumberOfTouches = 1;
    [self.croppedView addGestureRecognizer:singlePan];
    
    [self.upperContainerCapturedView bringSubviewToFront:self.croppedView];
    
    [self detectEdges];
}
-(void)singlePan:(UIPanGestureRecognizer *)gesture{
    CGPoint posInStretch = [gesture locationInView:self.croppedView];
    if(gesture.state==UIGestureRecognizerStateBegan){
        [self.croppedView findPointAtLocation:posInStretch];
    }
    if(gesture.state==UIGestureRecognizerStateEnded){
        self.croppedView.activePoint.backgroundColor = [UIColor grayColor];
        self.croppedView.activePoint = nil;
        [self.croppedView checkangle:0];
    }
    [self.croppedView moveActivePointToLocation:posInStretch];
}

#pragma mark - VSCameraPermissionsViewControllerDelegate
- (void)vc:(VSCameraPermissionsViewController *)vc hasCameraPermissions:(BOOL)hasPermissions {
    NSLog(@"hasCameraPermissions");
    if (hasPermissions) {
        [self.cameraController startCameraInView:self.cameraView];
    }
}

#pragma mark - show camera
- (void)checkCameraPermissionsStatus {
    typeof (self) __weak welf = self;
    [self.cameraController checkAuthorizationWithCompletion:^(VSCameraStatus status) {
        typeof (self) __strong strongSelf = welf;
        if (strongSelf) {
            [strongSelf runCompletionWithStatus:status sender:self];
        }
    }];
}
- (void)runCompletionWithStatus:(VSCameraStatus)status sender:(id)sender {
    NSString* segueid = nil;
    if (status == VSCameraStatusAuthorized) {
        [self vc:nil hasCameraPermissions:YES];
        return;
    } else {
        if (status == VSCameraStatusRestricted) {
            self.message = @"You do not have access to Camera (Parental Control or Company policy) :( \n\nContact admin for details.";
            self.positiveBtnTitle = @"OK";
        } else if (status == VSCameraStatusDenied) {
            self.message = @"Please allow this app to access Camera to take pictures of Expense Receipts.";
            self.positiveBtnTitle = @"Open Camera Settings"; //XXX constant
        } else if (status == VSCameraStatusInDetermined) {
            self.message = @"In order to take pictures of receipts, we need acceess to your camera.\n\nPlease tap Allow on next system dialog.";
            self.positiveBtnTitle = @"Proceed";
        }
        segueid = @"segueCameraPermissionsHeadsUp";
    }
    
    typeof (self) __weak welf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        typeof (self) __strong strongSelf = welf;
        if (strongSelf) {
            [strongSelf performSegueWithIdentifier:segueid sender:sender];
        }
    });
}

- (void)startCamera {
    [self checkCameraPermissionsStatus];
}
- (BOCameraController*)cameraController {
	if (!_cameraController) {
		BOCameraController* cc = [[BOCameraController alloc] init];
		_cameraController = cc;
	}
	return _cameraController;
}

#pragma mark - view controller override
- (BOOL)prefersStatusBarHidden {
	return YES;
}
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([@"category" isEqualToString:segue.identifier]) {
        UINavigationController* navVC = (UINavigationController*)[segue destinationViewController];
        BOCategoryTableViewController* destVC = (BOCategoryTableViewController*)[[navVC viewControllers] firstObject];
        destVC.delegateCategory = self;
    } else if ([@"segueCameraPermissionsHeadsUp" isEqualToString:segue.identifier]) {
        VSCameraPermissionsViewController* permissionsVC = (VSCameraPermissionsViewController*)[segue destinationViewController];
        permissionsVC.delegate = self;
        permissionsVC.cameraController = self.cameraController;
        permissionsVC.message = self.message;
        permissionsVC.positiveBtnTitle = self.positiveBtnTitle;
    } else if ([@"documents" isEqualToString:segue.identifier]) {
        //UINavigationController* navVC = (UINavigationController*)[segue destinationViewController];
        //BODocumentsListViewController* destVC = (BODocumentsListViewController*)[[navVC viewControllers] firstObject];
       // destVC.delegateCategory = self;
    }
}
#pragma mark - BOCategoryTableViewControllerDelegate
- (void)viewController:(BOCategoryTableViewController*)vc didSelectCategory:(NSString*)category {
    NSLog(@"didSelectCategory");
    self.categoryName = category;
    self.infoEntryView.labelSelectedCategoryName.text = category;
}

#pragma mark - API calls
- (void)apiAddDocument {
    //and then in local storage (LMDB)
    long        fileSize            = 0; // XXX
    NSString*   docTitle            = self.infoEntryView.textFieldTitle.text;
    UIImage*    originalImage       = self.image;
    UIImage*    finalProcessedImage = self.finalProcessedImage;
    if (!finalProcessedImage) {
        finalProcessedImage = self.cropImage;
    }
    NSString*   categoryName        = self.categoryName;
    
    //add it in cache first...
    [self addInCache:docTitle finalProcessedImage:finalProcessedImage];
    

    [self.facade addDocument:originalImage
         finalProcessedImage:finalProcessedImage
                   doctTitle:docTitle
                categoryName:categoryName
                    fileSize:fileSize];
}
- (void)addInCache:(NSString*)docTitle
finalProcessedImage:(UIImage*)finalProcessedImage {
    NSDate* now = [NSDate date];
    NSString* formattedTime = nil;
    BORecentDocModel* model = [[BORecentDocModel alloc] initWithTitle:docTitle timeFormatted:formattedTime thumbnail:finalProcessedImage createdDate:now];
    [self.docCache addModel:model];
}

#pragma mark OpenCV
- (void)detectEdges {
    typeof (self) __weak welf = self;
    [self.facade apiDetectEdges:self.capturedImageView croppedView:self.croppedView completion:^{
        _initialRect = welf.capturedImageView.frame;
        final_Rect = welf.capturedImageView.frame;
    }];
}

- (void)doCropImage {
    NSLog(@"-------------------> START: CROP IMAGE");
    [self putUIInProcessingStart];
    typeof (self) __weak welf = self;
    [self.facade apiDoCropImage:self.capturedImageView
                                     croppedView:self.croppedView
                                           image:self.image completion:^(UIImage* aCroppedImage) {
                                               typeof (self) __strong strongSelf = welf;
                                               if (strongSelf) {
                                                   [strongSelf runCropCompletionWithCroppedImage:aCroppedImage];
                                               }
                                           }];
}

- (void)runCropCompletionWithCroppedImage:(UIImage*)aCroppedImage {
    self.cropImage = aCroppedImage;
    self.capturedImageView.image = aCroppedImage;
    self.croppedView.hidden = YES;
    
    [self transitMenuItemsToPreviewMode];
    [self populateFiltersMenu];
    [self showFiltersView];
    [self showInfoEntryView];
    
    [self putUIInProcessingFinished];
    NSLog(@"-------------------> END: CROP IMAGE");
}

#pragma mark - Activity indicator and disable other buttons
- (void)putUIInProcessingStart {
    self.activityIndicator.hidden = NO;
    [self.activityIndicator startAnimating];
    
    //hide right most button
    self.menuButtonSelect.hidden = YES;
    
    //other menu buttons become disabled
    
    //right most menu button itself should be disabled to avoid two taps
    self.menuButtonSelect.enabled = NO;
    self.menuButtonSelect.alpha = 0.35f;
    
    //back button - left most
    self.menuButtonBack.enabled = NO;
    self.menuButtonBack.alpha = 0.35f;
    
    //left rotate button
    self.menuButtonRotateLeft.enabled = NO;
    self.menuButtonRotateLeft.alpha = 0.35f;
    
    //right rotate button
    self.menuButtonRotateRight.enabled = NO;
    self.menuButtonRotateRight.alpha = 0.35f;
}

- (void)putUIInProcessingFinished {
    self.activityIndicator.hidden = YES;
    [self.activityIndicator stopAnimating];
    
    self.menuButtonSelect.hidden = NO;
    
    self.menuButtonSelect.enabled = YES;
    self.menuButtonSelect.alpha = 1.f;
    
    //back button - left most
    self.menuButtonBack.enabled = YES;
    self.menuButtonBack.alpha = 1.f;
    
    //left rotate button
    self.menuButtonRotateLeft.enabled = YES;
    self.menuButtonRotateLeft.alpha = 1.f;
    
    //right rotate button
    self.menuButtonRotateRight.enabled = YES;
    self.menuButtonRotateRight.alpha = 1.f;
}

#pragma mark Roate left and right
- (CATransform3D)rotateTransform:(CATransform3D)initialTransform clockwise:(BOOL)clockwise
{
    CGFloat arg = _rotateSlider*M_PI;
    if(!clockwise){
        arg *= -1;
    }
    
    CATransform3D transform = initialTransform;
    transform = CATransform3DRotate(transform, arg, 0, 0, 1);
    transform = CATransform3DRotate(transform, 0*M_PI, 0, 1, 0);
    transform = CATransform3DRotate(transform, 0*M_PI, 1, 0, 0);
    
    return transform;
}

- (void)rotateStateDidChange
{
    CATransform3D transform = [self rotateTransform:CATransform3DIdentity clockwise:YES];
    
    CGFloat arg = _rotateSlider*M_PI;
    CGFloat Wnew = fabs(_initialRect.size.width * cos(arg)) + fabs(_initialRect.size.height * sin(arg));
    CGFloat Hnew = fabs(_initialRect.size.width * sin(arg)) + fabs(_initialRect.size.height * cos(arg));
    
    CGFloat Rw = final_Rect.size.width / Wnew;
    CGFloat Rh = final_Rect.size.height / Hnew;
    CGFloat scale = MIN(Rw, Rh) * 1;
    transform = CATransform3DScale(transform, scale, scale, 1);
    self.capturedImageView.layer.transform = transform;
    self.croppedView.layer.transform = transform;
    
    //    NSLog(@"%@",_sourceImageView);
}

@end
