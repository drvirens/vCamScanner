//
//  PhotoController.h
//  Bowen Swift
//
//  Created by Bennett Smith on 6/2/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PhotoController : NSObject
- (void)addPhotoWithName:(NSString *)name image:(UIImage *)image;
- (void)removePhotoWithName:(NSString *)name;
- (void)removeAllPhotos;
- (UIImage *)photoWithName:(NSString *)name;
@end
