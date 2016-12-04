//
//  vsImageProcessor.hpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/3/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef vsImageProcessor_hpp
#define vsImageProcessor_hpp

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

struct vsCGPoint {
    double x;
    double y;
};
typedef struct vsCGPoint vsCGPoint;


class vsImageProcessor
{
public:
    static void find_largest_square(const std::vector<std::vector<cv::Point> >& squares, std::vector<cv::Point>& biggest_square);
    static void find_squares(cv::Mat& image, std::vector<std::vector<cv::Point>>&squares);
    static double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0);
    static cv::Mat debugSquares( std::vector<std::vector<cv::Point> > squares, cv::Mat image );
    static void crop(cv::Mat& original,
                     double scaleFactor,
                     vsCGPoint ptBottomLeft,
                     vsCGPoint ptBottomRight,
                     vsCGPoint ptTopRight,
                     vsCGPoint ptTopLeft,
                     cv::Mat*& undistorted);
};

#endif /* vsImageProcessor_hpp */
