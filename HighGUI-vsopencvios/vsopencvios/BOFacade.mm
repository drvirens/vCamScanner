//
//  BOFacade.m
//  vsopencvios
//
//  Created by Virendra Shakya on 12/3/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include <string>

#import "BOFacade.h"
#import "BOPhotoController.h"
#import "BOLocationController.h"

#include "app_server.hpp"
#include "model_immutable_login.hpp"
#include "trace.h"

@interface BOFacade ()
@property (nonatomic) BOPhotoController *photoController;
@property (nonatomic, strong) BOLocationController *locationController;

@property (nonatomic) NSOperationQueue* operationQueue;
@property (nonatomic, copy) NSString* originalImageHref;
@property (nonatomic, copy) NSString* finalImageHref;
@end

@implementation BOFacade {
    CAppServer* app_;
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
}

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


#pragma mark - private
- (void)doBootStrap {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
    NSString *libraryDirectory = [paths objectAtIndex:0];
    string path = [libraryDirectory UTF8String];
    app_ = new CAppServer(path);
    app_->createRepository();
    app_->addAwesomeSauceAndViren();
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

- (void) doAddDocument:(UIImage*)image
 finalProcessedImage:(UIImage*)finalProcessedImage
           doctTitle:(NSString*)docTitle
        categoryName:(NSString*)categoryName
            fileSize:(NSInteger)fileSize {
    NSLog(@"doAddDocument");
    
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
    
    [self.operationQueue addOperation:operationSaveOriginalImage];
    [self.operationQueue addOperation:operationSaveFinalImage];
    [self.operationQueue addOperation:operationLmdbPut];
    
    //add operations
}

- (NSString*)saveImage:(UIImage*)image name:(NSString*)name {
    NSString* path = @"PATH";
    NSString* n = [NSString stringWithFormat:@"poofie_%@", name];
    NSURL* url = [self.photoController addPhotoWithName:n image:image];
    path = [url absoluteString];
    return path;
}

- (void) insertDocument:(NSString*)docTitle
          categoryName:(NSString*)categoryName
              fileSize:(NSInteger)fileSize
originalImageHref:(NSString*)originalImageHref
finalImageHref:(NSString*)finalImageHref {
    NSLog(@"doAddDocument");
}

@end
