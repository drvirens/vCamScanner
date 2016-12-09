//
//  BOFacade.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/3/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include <string>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "vsImageProcessor.hpp"
#include "trace.h"
#include "app_server.hpp"
#include "model_immutable_login.hpp"
#include "trace.h"

#import "BOFacade.h"
#import "BOPhotoController.h"
#import "BOLocationController.h"
#import "UIImageView+ContentFrame.h"
#import "MMOpenCVHelper.h"
#import "BODetectEdges.h"
#import "BODocumentModel.h"

static NSMutableArray* gArray = nil;

@interface BOFacade ()
@property (nonatomic) BOPhotoController *photoController;
@property (nonatomic, strong) BOLocationController *locationController;

@property (nonatomic) NSOperationQueue* operationQueue;
@property (nonatomic, copy) NSString* originalImageHref;
@property (nonatomic, copy) NSString* finalImageHref;

@property (nonatomic) BODetectEdges* detectEdgesAlgorithm;

@property (nonatomic) NSOperationQueue* mainQueue;
@end

@implementation BOFacade {
    CAppServer* app_;
    vsLinkedList<const vsModelBase>* linkedlistAllDocs_;
}

- (instancetype)init {
    if (self = [super init]) {
        [self commonInit];
    }
    return self;
}

- (void)commonInit {
    self.locationController = nil; //[[BOLocationController alloc] init]; // XXX - Location in Phase 2 - dont allocate else it will trigger location permissions
    self.photoController = [[BOPhotoController alloc] init];
    self.operationQueue = [[NSOperationQueue alloc] init];
    self.mainQueue = [NSOperationQueue mainQueue];
}

// ALL APIs must be executed on background thread
#pragma mark - APIs
- (void)bootStrap {
    typeof (self) __weak welf = self;
    NSBlockOperation* operation = [NSBlockOperation blockOperationWithBlock:^{
        typeof (self) __strong strongSelf = welf;
        if (strongSelf) {
            [strongSelf doBootStrap];
        }
    }];
    
    [self.operationQueue addOperation:operation];
}

- (void) addDocument:(UIImage*)image
 finalProcessedImage:(UIImage*)finalProcessedImage
           doctTitle:(NSString*)docTitle
        categoryName:(NSString*)categoryName
            fileSize:(NSInteger)fileSize {
    NSLog(@"add document here");
    
    typeof (self) __weak welf = self;
    NSBlockOperation* operation = [NSBlockOperation blockOperationWithBlock:^{
        typeof (self) __strong strongSelf = welf;
        if (strongSelf) {
            [strongSelf doAddDocument:image
                  finalProcessedImage:finalProcessedImage
                            doctTitle:docTitle
                         categoryName:categoryName
                             fileSize:fileSize];
        }
    }];
    
    [self.operationQueue addOperation:operation];
}


#pragma mark - bootstrap
- (void)doBootStrap {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
    NSString *libraryDirectory = [paths objectAtIndex:0];
    string path = [libraryDirectory UTF8String];
    app_ = new CAppServer(path);
    app_->createRepository();
    
    //app_->addAwesomeSauceAndViren();
    
    auto blockAuthCompletion = [&](const EAuthenticationStatus& aEAuthenticationStatus, const vsUser& aAuthenticatedUser)
    {
        LOG("dont care if it fails for now");
    };
    
    string theUserName                     = "awesomeSauce";
    string thePassword                     = "awesomesaucePassword";
    string theSecurity                     = "SASL";
    
    TLoginMessageLayout credentials(theUserName, thePassword, theSecurity);
    app_->authenticate(credentials, blockAuthCompletion);

}

#pragma mark - Add Document
- (void) doAddDocument:(UIImage*)image
 finalProcessedImage:(UIImage*)finalProcessedImage
           doctTitle:(NSString*)docTitle
        categoryName:(NSString*)categoryName
            fileSize:(NSInteger)fileSize {
            
    //operation 1 = save original image on disc and get its path
    typeof (self) __weak welf = self;
    NSBlockOperation* operationSaveOriginalImage = [NSBlockOperation blockOperationWithBlock:^{
        typeof (self) __strong strongSelf = welf;
        if (strongSelf) {
            strongSelf.originalImageHref = [strongSelf saveImage:image name:@"original"];
        }
    }];
    
    //operation 2 = save finalImage on disc and get its path
    NSBlockOperation* operationSaveFinalImage = [NSBlockOperation blockOperationWithBlock:^{
        typeof (self) __strong strongSelf = welf;
        if (strongSelf) {
            strongSelf.finalImageHref = [strongSelf saveImage:finalProcessedImage name:@"finalProcessedImage"];
        }
    }];
    
    //operation 3 = insert entry of vsDocument in LMDB
    NSBlockOperation* operationLmdbPut = [NSBlockOperation blockOperationWithBlock:^{
        typeof (self) __strong strongSelf = welf;
        if (strongSelf) {
            [strongSelf insertDocument:docTitle categoryName:categoryName fileSize:fileSize
                     originalImageHref:self.originalImageHref finalImageHref:self.finalImageHref];
        }
    }];
    
    //add dependnecy : 3 -> 2 -> 1
    [operationLmdbPut addDependency:operationSaveFinalImage];
    [operationSaveFinalImage addDependency:operationSaveOriginalImage];
    
    //add operations
    [self.operationQueue addOperation:operationSaveOriginalImage];
    [self.operationQueue addOperation:operationSaveFinalImage];
    [self.operationQueue addOperation:operationLmdbPut];
}

- (NSString*)saveImage:(UIImage*)image name:(NSString*)originalOrProcessed {
    string label = [originalOrProcessed UTF8String];
    string imagename;
    app_->generateImageName(label, imagename);
    NSString* n = [NSString stringWithUTF8String:imagename.c_str()];
    NSURL* url = [self.photoController addPhotoWithName:n image:image];
    NSString* path = [url absoluteString];
    return path;
}

- (void) insertDocument:(NSString*)docTitle
          categoryName:(NSString*)categoryName
              fileSize:(NSInteger)fileSizeProcessed
     originalImageHref:(NSString*)originalImageHref
        finalImageHref:(NSString*)finalImageHref {
    NSLog(@"insertDocument");
    
    string aTitle = [docTitle UTF8String];
    
    time_t rawtime;
    time (&rawtime);
    
    vs_uint64_t aDateCreated = rawtime;
    vs_uint64_t aDateUpdated = rawtime;
    vs_uint64_t aSize = fileSizeProcessed;
    string aOriginalPhotoHref = [originalImageHref UTF8String];
    string aModifiedLargePhotoHref = [finalImageHref UTF8String];
    string aFileType = [categoryName UTF8String];
    vsDocument doc(aTitle, aDateCreated, aDateUpdated, aSize, aOriginalPhotoHref, aModifiedLargePhotoHref, aFileType);
    
    app_->addDocument(doc, [](const vsDocument& savedDocument) {
        string primaryKey = savedDocument.docID();
        LOG("\n added document \n");
    });
}

#pragma mark - detect edge

- (void)apiDetectEdges:(UIImageView*)capturedImageView
           croppedView:(MMCropView*)croppedView
            completion:( void(^)() )completion {
    if (!self.detectEdgesAlgorithm) {
        self.detectEdgesAlgorithm = [[BODetectEdges alloc] init];
    }
    [self.detectEdgesAlgorithm apiDetectEdges:capturedImageView croppedView:croppedView completion:completion];
}

#pragma mark - crop image
- (UIImage*)apiDoCropImage:(UIImageView*)capturedImageView
               croppedView:(MMCropView*)croppedView
                     image:(UIImage*)image
                completion:( void(^)(UIImage*) )completion {
    UIImage* retImgae = nil;
    if([croppedView frameEdited]) {
        typeof (self) __weak welf = self;
        NSBlockOperation* cropBlock = [NSBlockOperation blockOperationWithBlock:^{
            typeof (self) __strong strongSelf = welf;
            if (strongSelf) {
                [strongSelf operationDoCropImage:capturedImageView croppedView:croppedView image:image completion:completion];
            }
        }];
        [self.operationQueue addOperation:cropBlock];
    }
    else{
        dispatch_async(dispatch_get_main_queue(), ^{
            UIAlertView  *alertView = [[UIAlertView alloc] initWithTitle:@"MMCamScanner" message:@"Invalid Rect" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
            [alertView show];
        });
    }
    
    return retImgae;
}

- (void)operationDoCropImage:(UIImageView*)capturedImageView
               croppedView:(MMCropView*)croppedView
                     image:(UIImage*)image
                completion:( void(^)(UIImage*) )completion {
    double scaleFactor =  [capturedImageView contentScale];
    
    CGPoint thePtBottomLeft = [croppedView coordinatesForPoint:1 withScaleFactor:scaleFactor];
    CGPoint thePtBottomRight = [croppedView coordinatesForPoint:2 withScaleFactor:scaleFactor];
    CGPoint thePtTopRight = [croppedView coordinatesForPoint:3 withScaleFactor:scaleFactor];
    CGPoint thePtTopLeft = [croppedView coordinatesForPoint:4 withScaleFactor:scaleFactor];
    
    cv::Mat* undistorted = NULL; //output
    cv::Mat original = [MMOpenCVHelper cvMatFromUIImage:image];
    
    vsCGPoint ptBottomLeft = {thePtBottomLeft.x, thePtBottomLeft.y};
    vsCGPoint ptBottomRight = {thePtBottomRight.x, thePtBottomRight.y};
    vsCGPoint ptTopRight = {thePtTopRight.x, thePtTopRight.y};
    vsCGPoint ptTopLeft = {thePtTopLeft.x, thePtTopLeft.y};
    
    vsImageProcessor::crop(original, scaleFactor, ptBottomLeft, ptBottomRight, ptTopRight, ptTopLeft, undistorted);
    
    UIImage* theCroppedImage = [MMOpenCVHelper UIImageFromCVMat:*undistorted];
    
    original.release();
    undistorted->release();
    delete undistorted;
    
    if (completion) {
        dispatch_async(dispatch_get_main_queue(), ^{
            completion(theCroppedImage);
        });
    }
}

#pragma mark - get all documents
static void visitNode(void* aData)
    {
//    if (gArray) {
//        [gArray removeAllObjects];
//        gArray = nil;
//        gArray = [NSMutableArray array];
//    }
//    if (!gArray) {
//        gArray = [NSMutableArray array];
//    }
    
    vsDocument* doc = (vsDocument*)aData;
    if (doc) 
        {
        LOG("\n got docuemnt \n");
        NSString* title = [NSString stringWithUTF8String:doc->title().c_str()];
        NSString* icon = @"ic_card_travel_white";
        
        
        string processedfinalImage = doc->modifiedLargePhotoHref();
        NSString* image = [NSString stringWithUTF8String:processedfinalImage.c_str()];
        NSString* onlyImageName = [image lastPathComponent];
        
        BODocumentModel* model = [[BODocumentModel alloc] initWithTitle:title
                                                        icon:icon 
                                                        date:[NSDate date] 
                                                        image:onlyImageName];
        [gArray addObject:model];
        }
    }

- (void)getAllDocuments:( void(^)(NSMutableArray*) )block {
    typeof (self) __weak welf = self;
    NSBlockOperation* getalldocsOperation = [NSBlockOperation blockOperationWithBlock:^{
        typeof (self) __strong strongSelf = welf;
        if (strongSelf) {
            [strongSelf doGetAllDocuments:block];
        }
    }];
    [self.operationQueue addOperation:getalldocsOperation];
}

static void deleteNode(void* aData) {
    vsDocument* doc = (vsDocument*)aData;
    if (doc) {
        delete doc;
    }
}

- (void)doGetAllDocuments:( void(^)(NSMutableArray*) )block { TRACE
    if (linkedlistAllDocs_) {
        linkedlistAllDocs_->deleteAll(deleteNode);
        delete linkedlistAllDocs_;
        linkedlistAllDocs_ = 0;
    }
    linkedlistAllDocs_ = new vsLinkedList<const vsModelBase>();
    
    if (gArray) {
        [gArray removeAllObjects];
        gArray = nil;
    }
    gArray = [NSMutableArray array];
    
    app_->getAllDocuments(*linkedlistAllDocs_, [&]() {
        linkedlistAllDocs_->traverse(visitNode);
        
        //run completion on main thread
        if (block) {
            NSBlockOperation* completion = [NSBlockOperation blockOperationWithBlock:^{
                block(gArray);
            }];
            [self.mainQueue addOperation:completion];
        }
    });
}

- (NSURL *)urlForPhotoStorage {
    return [self.photoController urlForPhotoStorage];
}

- (NSString*)imageSizeInStringFormat:(NSUInteger)size {
    NSString* ret = nil;
    NSString* units = nil;
    NSUInteger number = 0;
    if (size < 1024) {
        units = @"BYTES";
        number = size;
    } else {
        NSUInteger kb = size / 1024;
        if (kb < 1024) {
            units = @"KB";
            number = kb;
        } else {
            NSUInteger mb = size / (1024 * 1024);
            if (mb < 1024) {
                units = @"MB";
                number = mb;
            } else {
                NSUInteger gb = size / (1024 * 1024 * 1024);
                units = @"GB";
                number = gb;
            }
        }
    }
    ret = [NSString stringWithFormat:@"%ld %@", number, units];
    return ret;
}

- (NSString*)generateDefaultTitle {
    string doctitle;
    app_->generateDefaultDocTitle("doc", doctitle);
    NSString* ret = [NSString stringWithUTF8String:doctitle.c_str()];
    return ret;
}

@end
