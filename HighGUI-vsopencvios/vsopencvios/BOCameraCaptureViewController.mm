//
//  BOCameraCaptureViewController.m
//  Bowen Swift
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

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

typedef enum BOState {
    BONotCroppedState,
    BOCroppedPreviewState,
    BOShareState
} BOState;

static void* gUserLoadContext = &gUserLoadContext;

@interface BOCameraCaptureViewController () <UICollectionViewDelegate, UICollectionViewDataSource, UITextFieldDelegate, BOCategoryTableViewControllerDelegate, VSCameraPermissionsViewControllerDelegate>
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


@property (nonatomic) UIImage* image;
@property (nonatomic) UIImage* cropImage;
@property (nonatomic) UIImage* finalProcessedImage;

@property (strong, nonatomic) MMCropView* croppedView;

@property (nonatomic) BOState state;

@property (weak, nonatomic) IBOutlet NSLayoutConstraint *bottomFiltersViewConstraint;
@property (weak, nonatomic) IBOutlet BOFiltersView *filtersMenuView;

@property (nonatomic) NSMutableArray* dataSource;

@property (nonatomic) UICollectionViewCell* currentlySelectedFilterMenu;

@property (weak, nonatomic) IBOutlet NSLayoutConstraint *infoViewTopMarginLayoutConstraint;
@property (weak, nonatomic) IBOutlet BOInfoEntryView *infoEntryView;

@property (weak, nonatomic) IBOutlet UIButton *buttonSettings;
@property (weak, nonatomic) IBOutlet UIButton *buttonShowAllDocuments;


@property (nonatomic) BOOL entryInfoPartiallyHidden;

//camera permissions
@property (nonatomic, copy) NSString* message;
@property (nonatomic, copy) NSString* positiveBtnTitle;

@end

@implementation BOCameraCaptureViewController {
    CGRect _initialRect;
    CGRect final_Rect;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.state = BONotCroppedState;
    
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
    
	[self startCamera];
}
- (void)clearTitle {
    //placeholder
    NSDictionary* placeholderTextColor = @{
                                           NSForegroundColorAttributeName : [VSBranding vs_veryVeryDarkGrayColor],
                                           NSFontAttributeName : VS_FONT_VERYSMALL
                                           };
    NSAttributedString* placeHolder = [[NSAttributedString alloc] initWithString:@"ENTER TITLE" attributes:placeholderTextColor];
    self.infoEntryView.textFieldTitle.attributedPlaceholder = placeHolder;
    
    //typed text
    self.infoEntryView.textFieldTitle.font = VS_FONT_SMALL;
    self.infoEntryView.textFieldTitle.textColor = [UIColor darkGrayColor];
    self.infoEntryView.textFieldTitle.text = nil;
}
- (void)clearCategoryText {
    //category label
    NSDictionary* labelCategory = @{
                                    NSForegroundColorAttributeName : [VSBranding vs_veryVeryDarkGrayColor],
                                    NSFontAttributeName : VS_FONT_VERYSMALL
                                    };
    NSAttributedString* category = [[NSAttributedString alloc] initWithString:@"SELECT CATEGORY" attributes:labelCategory];
    self.infoEntryView.labelSelectedCategoryName.attributedText = category;
}
- (void)setupFileSizeLabel {
    self.infoEntryView.labelFileSize.textColor = [VSBranding vs_brandRedColor];
    self.infoEntryView.labelFileSize.font = VS_FONT_EXTRASMALL;
    self.infoEntryView.labelFileSize.alpha = 0.5f;
}
- (void)decorateCategoryMoreIcon {
    UIImage* rightArrow = [UIImage imageNamed:@"ic_keyboard_arrow_right_white"];
    rightArrow = [rightArrow imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    self.infoEntryView.imageViewIcon.image = rightArrow;
    self.infoEntryView.imageViewIcon.tintColor = [VSBranding vs_brandRedColor];
}
- (void)decorateSettingsButton {
    UIImage* settings = [UIImage imageNamed:@"ic_settings_white"];
    settings = [settings imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    [self.buttonSettings setImage:settings forState:UIControlStateNormal];
    self.buttonSettings.tintColor = [VSBranding vs_brandRedColor];
}
- (void)decorateShowDocumentsButton {
    UIImage* settings = [UIImage imageNamed:@"ic_view_list_white"];
    settings = [settings imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    [self.buttonShowAllDocuments setImage:settings forState:UIControlStateNormal];
    self.buttonShowAllDocuments.tintColor = [VSBranding vs_brandRedColor];
}
- (void)setupMiscGUI {
    self.infoEntryView.textFieldTitle.delegate = self;
    
    //category view tap detect
    self.infoEntryView.categoryView.userInteractionEnabled = YES;
    UITapGestureRecognizer* singleTapCategoryView = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(didSelectCateogry:)];
    singleTapCategoryView.numberOfTapsRequired = 1;
    [self.infoEntryView.categoryView addGestureRecognizer:singleTapCategoryView];
    
    //drag view
    self.infoEntryView.dragView.layer.cornerRadius = 2.5f;
    self.infoEntryView.dragViewSmaller.layer.cornerRadius = 2.f;
    //drag container tap event (Phase 2 = Pan gesture)
    UITapGestureRecognizer* singleTapDragView = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(didSelectDragView:)];
    singleTapDragView.numberOfTapsRequired = 1;
    [self.infoEntryView.dragContainerView addGestureRecognizer:singleTapDragView];
    
    //upper container captured view tap
    UITapGestureRecognizer* upperContainerCapturedViewTapped = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(didTapOnUpperContainerCapturedView:)];
    singleTapDragView.numberOfTapsRequired = 1;
    [self.upperContainerCapturedView addGestureRecognizer:upperContainerCapturedViewTapped];
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
    //hide settings button
    self.buttonSettings.hidden = YES;
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
    self.activityIndicator.hidden = NO;
    self.cameraView.hidden = YES;
    
    [self detectEdgesOnImageAndDisplay:self.image];
}
- (void)hideInfoEntryView {
    [self.view layoutIfNeeded];
    self.infoViewTopMarginLayoutConstraint.constant = -(kTopMarginEntryView);
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
}
- (void)showInfoEntryView {
    [self.view layoutIfNeeded];
    self.infoViewTopMarginLayoutConstraint.constant = 0;
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
}
- (void)hideInfoEntryViewPartially {
    [self.view layoutIfNeeded];
    self.infoViewTopMarginLayoutConstraint.constant = -(kTopMarginEntryView - 40);
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
    self.entryInfoPartiallyHidden = YES;
}
- (void)showInfoEntryViewPartially {
    [self.view layoutIfNeeded];
    self.infoViewTopMarginLayoutConstraint.constant = 0;
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
    self.entryInfoPartiallyHidden = NO;
}
- (void)hideInfoEntryViewPartiallyAndDisableDragger {
    [self.view layoutIfNeeded];
    self.infoViewTopMarginLayoutConstraint.constant = -(kTopMarginEntryView - 40);
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
    self.entryInfoPartiallyHidden = NO;
    self.infoEntryView.userInteractionEnabled = NO;
    
    self.infoEntryView.dragView.hidden = YES;
    self.infoEntryView.dragViewSmaller.hidden = YES;
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

#pragma mark - 4 menu buttons
- (IBAction)didSelectMenuGoBack:(id)sender {
    [self hideBottomMenu];
    [self showCameraOverlay];
    
    self.containerCapturedView.hidden = YES;
    self.activityIndicator.hidden = YES;
    self.cameraView.hidden = NO;
    
    [self.croppedView removeFromSuperview];
    self.croppedView = nil;
    
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
    
    self.buttonSettings.hidden = NO;
    [self clearTitle];
    [self clearCategoryText];
    self.infoEntryView.userInteractionEnabled = YES;
    self.infoEntryView.dragView.hidden = NO;
    self.infoEntryView.dragViewSmaller.hidden = NO;
}
- (IBAction)didSelectMenuRotateLeft:(id)sender {
}
- (IBAction)didSelectMenuRotateRight:(id)sender {
}
- (IBAction)didSelectMenuSelect:(id)sender {
    if (self.state == BOCroppedPreviewState) {
        NSLog(@"BOCroppedPreviewState - show share state/view");
        [self hideInfoEntryViewPartiallyAndDisableDragger]; //disable drag and remove the dragger - use
        [self hideFiltersView];
        [self transitMenuItemsToShareMode];
    } else if (self.state == BOShareState) {
        [self share:self];
    } else {
        [self doCropImage];
        [self transitMenuItemsToPreviewMode];
        [self populateFiltersMenu];
        [self showFiltersView];
        [self showInfoEntryView];
    }
}
- (void)setupDefaultNextActionButton {
    UIImage* rightArrow = [UIImage imageNamed:@"ic_check_white"];
    rightArrow = [rightArrow imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    [self.menuButtonSelect setBackgroundImage:rightArrow forState:UIControlStateNormal];
    self.menuButtonSelect.tintColor = [VSBranding vs_brandRedColor];
}
- (void)transitMenuItemsToPreviewMode {
    self.menuButtonRotateLeft.hidden = YES;
    self.menuButtonRotateRight.hidden = YES;
    UIImage* rightArrow = [UIImage imageNamed:@"ic_arrow_forward_white"];
    rightArrow = [rightArrow imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    [self.menuButtonSelect setBackgroundImage:rightArrow forState:UIControlStateNormal];
    self.menuButtonSelect.tintColor = [VSBranding vs_brandRedColor];
    self.state = BOCroppedPreviewState;
}
- (void)transitMenuItemsToNotCroppedMode {
    self.menuButtonRotateLeft.hidden = NO;
    self.menuButtonRotateRight.hidden = NO;
    UIImage* rightArrow = [UIImage imageNamed:@"ic_check_white"];
    rightArrow = [rightArrow imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    [self.menuButtonSelect setBackgroundImage:rightArrow forState:UIControlStateNormal];
    self.menuButtonSelect.tintColor = [VSBranding vs_brandRedColor];
    self.state = BOCroppedPreviewState;
}
- (void)transitMenuItemsToShareMode {
    self.menuButtonRotateLeft.hidden = YES;
    self.menuButtonRotateRight.hidden = YES;
    UIImage* rightArrow = [UIImage imageNamed:@"ic_share_white"];
    rightArrow = [rightArrow imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    [self.menuButtonSelect setBackgroundImage:rightArrow forState:UIControlStateNormal];
    self.menuButtonSelect.tintColor = [VSBranding vs_brandRedColor];
    self.state = BOShareState;
}
- (void)share:(id)sender {
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
    [self presentViewController:activityViewControntroller animated:true completion:nil];
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
    
    //[self setCropUI];
    [self.upperContainerCapturedView bringSubviewToFront:self.croppedView];
    
    [self detectEdges];
    _initialRect = self.capturedImageView.frame;
    final_Rect =self.capturedImageView.frame;
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
        //segueid = @"segueCamera";
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
    
	//[self.cameraController startCameraInView:self.cameraView];
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
    }
}
#pragma mark - BOCategoryTableViewControllerDelegate
- (void)viewController:(BOCategoryTableViewController*)vc didSelectCategory:(NSString*)category {
    NSLog(@"didSelectCategory");
    self.infoEntryView.labelSelectedCategoryName.text = category;
}

#pragma mark OpenCV
- (void)detectEdges
{
    cv::Mat original = [MMOpenCVHelper cvMatFromUIImage:self.capturedImageView.image];
    CGSize targetSize = self.capturedImageView.contentSize;
    cv::resize(original, original, cvSize(targetSize.width, targetSize.height));
    
    std::vector<std::vector<cv::Point>>squares;
    std::vector<cv::Point> largest_square;
    
    find_squares(original, squares);
    find_largest_square(squares, largest_square);
    
    if (largest_square.size() == 4)
    {
        // Manually sorting points, needs major improvement. Sorry.
        NSMutableArray *points = [NSMutableArray array];
        NSMutableDictionary *sortedPoints = [NSMutableDictionary dictionary];
        
        for (int i = 0; i < 4; i++)
        {
            NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys:[NSValue valueWithCGPoint:CGPointMake(largest_square[i].x, largest_square[i].y)], @"point" , [NSNumber numberWithInt:(largest_square[i].x + largest_square[i].y)], @"value", nil];
            [points addObject:dict];
        }
        
        int min = [[points valueForKeyPath:@"@min.value"] intValue];
        int max = [[points valueForKeyPath:@"@max.value"] intValue];
        
        int minIndex = 0;
        int maxIndex = 0;
        
        int missingIndexOne = 0;
        int missingIndexTwo = 0;
        
        for (int i = 0; i < 4; i++)
        {
            NSDictionary *dict = [points objectAtIndex:i];
            
            if ([[dict objectForKey:@"value"] intValue] == min)
            {
                [sortedPoints setObject:[dict objectForKey:@"point"] forKey:@"0"];
                minIndex = i;
                continue;
            }
            
            if ([[dict objectForKey:@"value"] intValue] == max)
            {
                [sortedPoints setObject:[dict objectForKey:@"point"] forKey:@"2"];
                maxIndex = i;
                continue;
            }
            
            NSLog(@"MSSSING %i", i);
            
            missingIndexOne = i;
        }
        
        for (int i = 0; i < 4; i++)
        {
            if (missingIndexOne != i && minIndex != i && maxIndex != i)
            {
                missingIndexTwo = i;
            }
        }
        
        
        if (largest_square[missingIndexOne].x < largest_square[missingIndexTwo].x)
        {
            //2nd Point Found
            [sortedPoints setObject:[[points objectAtIndex:missingIndexOne] objectForKey:@"point"] forKey:@"3"];
            [sortedPoints setObject:[[points objectAtIndex:missingIndexTwo] objectForKey:@"point"] forKey:@"1"];
        }
        else
        {
            //4rd Point Found
            [sortedPoints setObject:[[points objectAtIndex:missingIndexOne] objectForKey:@"point"] forKey:@"1"];
            [sortedPoints setObject:[[points objectAtIndex:missingIndexTwo] objectForKey:@"point"] forKey:@"3"];
        }
        
        [self.croppedView topLeftCornerToCGPoint:[(NSValue *)[sortedPoints objectForKey:@"0"] CGPointValue]];
        [self.croppedView topRightCornerToCGPoint:[(NSValue *)[sortedPoints objectForKey:@"1"] CGPointValue]];
        [self.croppedView bottomRightCornerToCGPoint:[(NSValue *)[sortedPoints objectForKey:@"2"] CGPointValue]];
        [self.croppedView bottomLeftCornerToCGPoint:[(NSValue *)[sortedPoints objectForKey:@"3"] CGPointValue]];
        
        NSLog(@"%@ Sorted Points",sortedPoints);
    }
    original.release();
}

// http://stackoverflow.com/questions/8667818/opencv-c-obj-c-detecting-a-sheet-of-paper-square-detection
static void find_squares(cv::Mat& image, std::vector<std::vector<cv::Point>>&squares) {
    
    // blur will enhance edge detection
    
    cv::Mat blurred(image);
    //    medianBlur(image, blurred, 9);
    GaussianBlur(image, blurred, cvSize(11,11), 0);//change from median blur to gaussian for more accuracy of square detection
    
    cv::Mat gray0(blurred.size(), CV_8U), gray;
    std::vector<std::vector<cv::Point> > contours;
    
    // find squares in every color plane of the image
    for (int c = 0; c < 3; c++)
    {
        int ch[] = {c, 0};
        mixChannels(&blurred, 1, &gray0, 1, ch, 1);
        
        // try several threshold levels
        const int threshold_level = 2;
        for (int l = 0; l < threshold_level; l++)
        {
            // Use Canny instead of zero threshold level!
            // Canny helps to catch squares with gradient shading
            if (l == 0)
            {
                Canny(gray0, gray, 10, 20, 3); //
                //                Canny(gray0, gray, 0, 50, 5);
                
                // Dilate helps to remove potential holes between edge segments
                dilate(gray, gray, cv::Mat(), cv::Point(-1,-1));
            }
            else
            {
                gray = gray0 >= (l+1) * 255 / threshold_level;
            }
            
            // Find contours and store them in a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
            
            // Test contours
            std::vector<cv::Point> approx;
            for (size_t i = 0; i < contours.size(); i++)
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(cv::Mat(contours[i]), approx, arcLength(cv::Mat(contours[i]), true)*0.02, true);
                
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if (approx.size() == 4 &&
                    fabs(contourArea(cv::Mat(approx))) > 1000 &&
                    isContourConvex(cv::Mat(approx)))
                {
                    double maxCosine = 0;
                    
                    for (int j = 2; j < 5; j++)
                    {
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }
                    
                    if (maxCosine < 0.3)
                        squares.push_back(approx);
                }
            }
        }
    }
}

static void find_largest_square(const std::vector<std::vector<cv::Point> >& squares, std::vector<cv::Point>& biggest_square)
{
    if (!squares.size())
    {
        // no squares detected
        return;
    }
    
    int max_width = 0;
    int max_height = 0;
    int max_square_idx = 0;
    
    for (size_t i = 0; i < squares.size(); i++)
    {
        // Convert a set of 4 unordered Points into a meaningful cv::Rect structure.
        cv::Rect rectangle = boundingRect(cv::Mat(squares[i]));

        // Store the index position of the biggest square found
        if ((rectangle.width >= max_width) && (rectangle.height >= max_height))
        {
            max_width = rectangle.width;
            max_height = rectangle.height;
            max_square_idx = i;
        }
    }
    
    biggest_square = squares[max_square_idx];
}

static double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 ) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

static cv::Mat debugSquares( std::vector<std::vector<cv::Point> > squares, cv::Mat image ){
    NSLog(@"DEBUG!/?!");
    for ( unsigned int i = 0; i< squares.size(); i++ ) {
        // draw contour
        NSLog(@"LOOP!");
        cv::drawContours(image, squares, i, cv::Scalar(255,0,0), 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
        
        // draw bounding rect
        cv::Rect rect = boundingRect(cv::Mat(squares[i]));
        cv::rectangle(image, rect.tl(), rect.br(), cv::Scalar(0,255,0), 2, 8, 0);
        
        // draw rotated rect
        cv::RotatedRect minRect = minAreaRect(cv::Mat(squares[i]));
        cv::Point2f rect_points[4];
        minRect.points( rect_points );
        for ( int j = 0; j < 4; j++ ) {
            cv::line( image, rect_points[j], rect_points[(j+1)%4], cv::Scalar(0,0,255), 1, 8 ); // blue
        }
    }
    return image;
}

- (void)doCropImage {
    if([self.croppedView frameEdited]){
        CGFloat scaleFactor =  [self.capturedImageView contentScale];
        CGPoint ptBottomLeft = [self.croppedView coordinatesForPoint:1 withScaleFactor:scaleFactor];
        CGPoint ptBottomRight = [self.croppedView coordinatesForPoint:2 withScaleFactor:scaleFactor];
        CGPoint ptTopRight = [self.croppedView coordinatesForPoint:3 withScaleFactor:scaleFactor];
        CGPoint ptTopLeft = [self.croppedView coordinatesForPoint:4 withScaleFactor:scaleFactor];
        
        CGFloat w1 = sqrt( pow(ptBottomRight.x - ptBottomLeft.x , 2) + pow(ptBottomRight.x - ptBottomLeft.x, 2));
        CGFloat w2 = sqrt( pow(ptTopRight.x - ptTopLeft.x , 2) + pow(ptTopRight.x - ptTopLeft.x, 2));
        CGFloat h1 = sqrt( pow(ptTopRight.y - ptBottomRight.y , 2) + pow(ptTopRight.y - ptBottomRight.y, 2));
        CGFloat h2 = sqrt( pow(ptTopLeft.y - ptBottomLeft.y , 2) + pow(ptTopLeft.y - ptBottomLeft.y, 2));
        
        CGFloat maxWidth = (w1 < w2) ? w1 : w2;
        CGFloat maxHeight = (h1 < h2) ? h1 : h2;
        
        cv::Point2f src[4], dst[4];
        src[0].x = ptTopLeft.x;
        src[0].y = ptTopLeft.y;
        src[1].x = ptTopRight.x;
        src[1].y = ptTopRight.y;
        src[2].x = ptBottomRight.x;
        src[2].y = ptBottomRight.y;
        src[3].x = ptBottomLeft.x;
        src[3].y = ptBottomLeft.y;
        
        dst[0].x = 0;
        dst[0].y = 0;
        dst[1].x = maxWidth - 1;
        dst[1].y = 0;
        dst[2].x = maxWidth - 1;
        dst[2].y = maxHeight - 1;
        dst[3].x = 0;
        dst[3].y = maxHeight - 1;
        
        cv::Mat undistorted = cv::Mat( cvSize(maxWidth,maxHeight), CV_8UC4);
        cv::Mat original = [MMOpenCVHelper cvMatFromUIImage:self.image];
        
        NSLog(@"%f %f %f %f",ptBottomLeft.x,ptBottomRight.x,ptTopRight.x,ptTopLeft.x);
        cv::warpPerspective(original, undistorted, cv::getPerspectiveTransform(src, dst), cvSize(maxWidth, maxHeight));
        
        self.capturedImageView.image=[MMOpenCVHelper UIImageFromCVMat:undistorted];
        self.cropImage = self.capturedImageView.image;
        self.croppedView.hidden = YES;
        
        original.release();
        undistorted.release();
    }
    else{
        UIAlertView  *alertView = [[UIAlertView alloc] initWithTitle:@"MMCamScanner" message:@"Invalid Rect" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alertView show];
    }
}

@end
