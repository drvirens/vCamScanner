//
//  BOPhotoController.h
//  Bowen Swift
//
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BOPhotoController : NSObject
- (void)addPhotoWithName:(NSString *)name image:(UIImage *)image;
- (void)removePhotoWithName:(NSString *)name;
- (void)removeAllPhotos;
- (UIImage *)photoWithName:(NSString *)name;
@end
