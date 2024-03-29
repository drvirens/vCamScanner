//
//  BOPhotoController.m
//  Bowen Swift
//
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "BOPhotoController.h"

@interface BOPhotoController()
- (NSURL *)urlForPhotoWithName:(NSString *)name;
@end

@implementation BOPhotoController

- (instancetype)init {
    self = [super init];
    if (self) {
        NSFileManager *fileManager = [NSFileManager defaultManager];
        BOOL isDirectory = NO;
        NSURL *photoStorageURL = [self urlForPhotoStorage];
        if ([fileManager fileExistsAtPath:[photoStorageURL path] isDirectory:&isDirectory] == NO) {
            [fileManager createDirectoryAtURL:photoStorageURL withIntermediateDirectories:YES attributes:nil error:nil];
        }
    }
    return self;
}

- (NSURL*)addPhotoWithName:(NSString *)name image:(UIImage *)image {
    NSData *imageData = UIImageJPEGRepresentation(image, 1.0f);
    NSURL *photoURL = [self urlForPhotoWithName:name];
    [imageData writeToURL:photoURL atomically:YES];
    imageData = nil;
    return photoURL;
}

- (void)removePhotoWithName:(NSString *)name {
    NSURL *photoURL = [self urlForPhotoWithName:name];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSError *error = nil;
    [fileManager removeItemAtURL:photoURL error:&error];
}

- (void)removeAllPhotos {
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSDirectoryEnumerator *photoEnumerator = [fileManager enumeratorAtURL:[self urlForPhotoStorage] includingPropertiesForKeys:@[NSURLNameKey, NSURLIsDirectoryKey] options:NSDirectoryEnumerationSkipsHiddenFiles errorHandler:nil];
    for (NSURL *photoURL in photoEnumerator) {
        NSNumber *isDirectory;
        [photoURL getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:nil];
        if (![isDirectory boolValue]) {
            [fileManager removeItemAtURL:photoURL error:nil];
        }
    }
}

- (UIImage *)photoWithName:(NSString *)name {
    NSURL *photoUrl = [self urlForPhotoWithName:name];
    NSData *imageData = [NSData dataWithContentsOfURL:photoUrl];
    UIImage *image = [UIImage imageWithData:imageData];
    return image;
}

- (NSURL *)urlForPhotoStorage {
    static NSURL *photoStorageURL = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        NSFileManager *fileManager = [NSFileManager defaultManager];
        photoStorageURL = [[fileManager URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];
        photoStorageURL = [photoStorageURL URLByAppendingPathComponent:@"vDocScanner"];
    });
    return photoStorageURL;
}

- (NSURL *)urlForPhotoWithName:(NSString *)name {
    NSURL *photoURL = [self urlForPhotoStorage];
    photoURL = [photoURL URLByAppendingPathComponent:name];
    photoURL = [photoURL URLByAppendingPathExtension:@"jpg"];
    return photoURL;
}

@end
