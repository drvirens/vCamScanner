//
//  BOCameraCaptureViewController.m
//  iSpyChallenge
//
//  Created by Virendra Shakya on 8/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOCameraCaptureViewController.h"
#import "BOCameraController.h"
#import "MMCropView.h"
#import "UIImageView+ContentFrame.h"
#import "MMOpenCVHelper.h"

//#include "file_utils_wrapper.h"
//#include "scannerLite.h"


static void* gUserLoadContext = &gUserLoadContext;

@interface BOCameraCaptureViewController ()
@property (nonatomic) BOCameraController* cameraController;
@property (weak, nonatomic) IBOutlet UIButton *buttonCameraCapture;

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


@property (nonatomic) UIImage* image;
@property (nonatomic) UIImage* cropImage;

@property (strong, nonatomic) MMCropView *cropRect;
@end

@implementation BOCameraCaptureViewController {
    CGRect _initialRect;
    CGRect final_Rect;
}
- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
	if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
		
	}
	return self;
}
- (void)viewDidLoad {
    [super viewDidLoad];
	[self setupContainerView];
	[self setupButton];
	[self startCamera];
}
- (void)setupContainerView {
	self.containerCapturedView.hidden = YES;
}
- (void)setupButton {
	self.buttonCameraCapture.layer.borderColor = [UIColor whiteColor].CGColor;
	self.buttonCameraCapture.layer.borderWidth = 6.f;
	self.buttonCameraCapture.layer.cornerRadius = 50.f; //XXX hardcoded for now
}
- (IBAction)didTapCapturePhoto:(id)sender {
	typeof (self) __weak welf = self;
	[self.cameraController capturePhotoWithCompletion:^(UIImage * image) {
		NSLog(@"did capture ");
		welf.image = image;
        self.capturedImageView.image = image;
        
		[welf showCapturedImageLoading];
        [welf detectEdgesOnImageAndDisplay:image];
	}];
}
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
    [self showBottomMenu];
    
	self.containerCapturedView.hidden = NO;
	self.activityIndicator.hidden = NO;
}
- (void)hideCameraOverlay {
    [self.view layoutIfNeeded];
    self.buttonCameraCaptureBottomConstraint.constant = -(100 + 10);
    [UIView animateWithDuration:.25 animations:^{
        [self.view layoutIfNeeded];
    }];
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
    self.lowerContainerCapturedViewBottomLayout.constant = -(120);
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
}
#pragma mark - 4 menu buttons
- (IBAction)didSelectMenuGoBack:(id)sender {
    [self hideBottomMenu];
    [self showCameraOverlay];
    
    self.containerCapturedView.hidden = YES;
    self.activityIndicator.hidden = YES;
}
- (IBAction)didSelectMenuRotateLeft:(id)sender {
}
- (IBAction)didSelectMenuRotateRight:(id)sender {
}
- (IBAction)didSelectMenuSelect:(id)sender {
    [self doCropImage];
}
#pragma mark - image crop view
- (void)prepareCropView {
    CGRect cropFrame = CGRectMake(self.capturedImageView.contentFrame.origin.x,
                                self.capturedImageView.contentFrame.origin.y + 30,
                                self.capturedImageView.contentFrame.size.width,
                                self.capturedImageView.contentFrame.size.height - 30 - 30 - 60);
    _cropRect= [[MMCropView alloc] initWithFrame:cropFrame];
    [self.upperContainerCapturedView addSubview:_cropRect];
    
    UIPanGestureRecognizer *singlePan = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(singlePan:)];
    singlePan.maximumNumberOfTouches = 1;
    [_cropRect addGestureRecognizer:singlePan];
    
    //[self setCropUI];
    [self.upperContainerCapturedView bringSubviewToFront:_cropRect];
    
    [self detectEdges];
    _initialRect = self.capturedImageView.frame;
    final_Rect =self.capturedImageView.frame;
}
-(void)singlePan:(UIPanGestureRecognizer *)gesture{
    CGPoint posInStretch = [gesture locationInView:_cropRect];
    if(gesture.state==UIGestureRecognizerStateBegan){
        [_cropRect findPointAtLocation:posInStretch];
    }
    if(gesture.state==UIGestureRecognizerStateEnded){
        _cropRect.activePoint.backgroundColor = [UIColor grayColor];
        _cropRect.activePoint = nil;
        [_cropRect checkangle:0];
    }
    [_cropRect moveActivePointToLocation:posInStretch];
}


#pragma mark - show camera
- (void)startCamera {
	[self.cameraController startCameraInView:self.view];
}
- (BOCameraController*)cameraController {
	if (!_cameraController) {
		BOCameraController* cc = [[BOCameraController alloc] init];
		_cameraController = cc;
	}
	return _cameraController;
}
- (BOOL)prefersStatusBarHidden {
	return YES;
}

#pragma mark - OpenCV


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
        
        [_cropRect topLeftCornerToCGPoint:[(NSValue *)[sortedPoints objectForKey:@"0"] CGPointValue]];
        [_cropRect topRightCornerToCGPoint:[(NSValue *)[sortedPoints objectForKey:@"1"] CGPointValue]];
        [_cropRect bottomRightCornerToCGPoint:[(NSValue *)[sortedPoints objectForKey:@"2"] CGPointValue]];
        [_cropRect bottomLeftCornerToCGPoint:[(NSValue *)[sortedPoints objectForKey:@"3"] CGPointValue]];
        
        NSLog(@"%@ Sorted Points",sortedPoints);
        
        
        
    }
    else{
        
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
        
        //        cout << "find_largest_square: #" << i << " rectangle x:" << rectangle.x << " y:" << rectangle.y << " " << rectangle.width << "x" << rectangle.height << endl;
        
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
    if([_cropRect frameEdited]){
        
        //Thanks To stackOverflow
        CGFloat scaleFactor =  [self.capturedImageView contentScale];
        CGPoint ptBottomLeft = [_cropRect coordinatesForPoint:1 withScaleFactor:scaleFactor];
        CGPoint ptBottomRight = [_cropRect coordinatesForPoint:2 withScaleFactor:scaleFactor];
        CGPoint ptTopRight = [_cropRect coordinatesForPoint:3 withScaleFactor:scaleFactor];
        CGPoint ptTopLeft = [_cropRect coordinatesForPoint:4 withScaleFactor:scaleFactor];
        
        
        
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
//        cv::Mat original = [MMOpenCVHelper cvMatFromUIImage:_adjustedImage];
        cv::Mat original = [MMOpenCVHelper cvMatFromUIImage:self.image];
        
        NSLog(@"%f %f %f %f",ptBottomLeft.x,ptBottomRight.x,ptTopRight.x,ptTopLeft.x);
        cv::warpPerspective(original, undistorted, cv::getPerspectiveTransform(src, dst), cvSize(maxWidth, maxHeight));
        
        [UIView transitionWithView:self.capturedImageView duration:0.3 options:UIViewAnimationOptionTransitionCrossDissolve animations:^{
            
            
            
            self.capturedImageView.image=[MMOpenCVHelper UIImageFromCVMat:undistorted];
            self.cropImage = self.capturedImageView.image;
            
            //         _sourceImageView.image = [MMOpenCVHelper UIImageFromCVMat:grayImage];//For gray image
            
        } completion:^(BOOL finished) {
            _cropRect.hidden=YES;
//            [UIView animateWithDuration:0.5 animations:^{
//                scrollView.frame=CGRectMake(0, 0, self.view.bounds.size.width, 64);
//                
//            }];
            
        }];
        
        original.release();
        undistorted.release();
        
        
        
    }
    else{
        UIAlertView  *alertView = [[UIAlertView alloc] initWithTitle:@"MMCamScanner" message:@"Invalid Rect" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alertView show];
        
    }
    

}

@end
