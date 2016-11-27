//
//  ViewController.m
//  vsopencvios
//
//  Created by Virendra Shakya on 11/18/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#import "ViewController.h"
#include "scannerLite.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //test+
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    NSString *outputPath = [documentsDirectory stringByAppendingPathComponent:@"viren.jpg"];
    NSLog(@"fileName to write = %@", outputPath);
    
    //make a file name to write the data to using the documents directory:
//    NSString *fileName = [NSString stringWithFormat:@"%@/dst1.jpg",
//                          documentsDirectory];
//    if (fileName) {
//        NSLog(@"fileName to write = %@", fileName);
//        //create content - four lines of text
//        NSString *content = @" ";
//        //save content to the documents directory
//        [content writeToFile:fileName
//                  atomically:NO
//                    encoding:NSStringEncodingConversionAllowLossy
//                       error:nil];
//    }
    
    //test-
    
    NSBundle* bundle = [NSBundle bundleForClass:[self class]];
    NSString* path = [bundle pathForResource:@"doc2" ofType:@"jpg"];
    if (path) {
        const char* thepath = [path UTF8String];
        const char* theOutputPath = [outputPath UTF8String];
        pleaseScan(thepath, theOutputPath);
    }
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
