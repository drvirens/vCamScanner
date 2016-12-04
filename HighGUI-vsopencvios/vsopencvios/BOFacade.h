//
//  BOFacade.h
//  vsopencvios
//
//  Created by Virendra Shakya on 12/3/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MMCropView.h"

@interface BOFacade : NSObject
- (void)bootStrap;

- (void) addDocument:(UIImage*)image
 finalProcessedImage:(UIImage*)finalProcessedImage
           doctTitle:(NSString*)docTitle
        categoryName:(NSString*)categoryName
            fileSize:(NSInteger)fileSize;

- (void)apiDetectEdges:(UIImageView*)capturedImageView
        croppedView:(MMCropView*)croppedView;

- (UIImage*)apiDoCropImage:(UIImageView*)capturedImageView
            croppedView:(MMCropView*)croppedView
                  image:(UIImage*)image
                completion:( void(^)(UIImage*) )completion;
@end
