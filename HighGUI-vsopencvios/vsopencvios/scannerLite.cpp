/* 
 * An OpenCV program implementing the recognition feature of the app "CamScanner". 
 * It extracts the main document object from an image and adjust it to A4 size. 
 */


#include "opencv2/opencv.hpp"
#include <algorithm>
#include <string>
#include <vector>

#include "scannerLite.h"
using namespace cv;
using namespace std;

vector<Point> getPoints(Mat image);

/**
 * Get edges of an image
 * @param gray - grayscale input image
 * @param canny - output edge image
 */
void getCanny(Mat gray, Mat &canny) {
  Mat thres;
  double high_thres = threshold(gray, thres, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU), low_thres = high_thres * 0.5;
  cv::Canny(gray, canny, low_thres, high_thres);
}

struct Line {
  Point _p1;
  Point _p2;
  Point _center;

  Line(Point p1, Point p2) {
    _p1 = p1;
    _p2 = p2;
    _center = Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
  }
};

bool cmp_y(const Line &p1, const Line &p2) {
  return p1._center.y < p2._center.y;
}

bool cmp_x(const Line &p1, const Line &p2) {
  return p1._center.x < p2._center.x;
}

/**
 * Compute intersect point of two lines l1 and l2
 * @param l1 
 * @param l2
 * @return Intersect Point
 */
Point2f computeIntersect(Line l1, Line l2) {
  int x1 = l1._p1.x, x2 = l1._p2.x, y1 = l1._p1.y, y2 = l1._p2.y;
  int x3 = l2._p1.x, x4 = l2._p2.x, y3 = l2._p1.y, y4 = l2._p2.y;
  if (float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)) {
    Point2f pt;
    pt.x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;
    pt.y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;
    return pt;
  }
  return Point2f(-1, -1);
}

vector<Point> scan(String file, String dstFile, bool debug = true) {

  /* get input image */
  Mat img = imread(file);
  // resize input image to img_proc to reduce computation
  Mat img_proc;
  int w = img.size().width, h = img.size().height, min_w = 200;

//#if 0
  double scale = min(10.0, w * 1.0 / min_w);
  int w_proc = w * 1.0 / scale, h_proc = h * 1.0 / scale;
  resize(img, img_proc, Size(w_proc, h_proc));
  Mat img_dis = img_proc.clone();

  /* get four outline edges of the document */
  // get edges of the image
  Mat gray, canny;
  cvtColor(img_proc, gray, CV_BGR2GRAY);
  getCanny(gray, canny);

  // extract lines from the edge image
  vector<Vec4i> lines;
  vector<Line> horizontals, verticals;
  HoughLinesP(canny, lines, 1, CV_PI / 180, w_proc / 3, w_proc / 3, 20);
  for (size_t i = 0; i < lines.size(); i++) {
    Vec4i v = lines[i];
    double delta_x = v[0] - v[2], delta_y = v[1] - v[3];
    Line l(Point(v[0], v[1]), Point(v[2], v[3]));
    // get horizontal lines and vertical lines respectively
    if (fabs(delta_x) > fabs(delta_y)) {
      horizontals.push_back(l);
    } else {
      verticals.push_back(l);
    }
    // for visualization only
    if (debug)
      line(img_proc, Point(v[0], v[1]), Point(v[2], v[3]), Scalar(0, 0, 255), 1, CV_AA);
  }

  // edge cases when not enough lines are detected
  if (horizontals.size() < 2) {
    if (horizontals.size() == 0 || horizontals[0]._center.y > h_proc / 2) {
      horizontals.push_back(Line(Point(0, 0), Point(w_proc - 1, 0)));
    }
    if (horizontals.size() == 0 || horizontals[0]._center.y <= h_proc / 2) {
      horizontals.push_back(Line(Point(0, h_proc - 1), Point(w_proc - 1, h_proc - 1)));
    }
  }
  if (verticals.size() < 2) {
    if (verticals.size() == 0 || verticals[0]._center.x > w_proc / 2) {
      verticals.push_back(Line(Point(0, 0), Point(0, h_proc - 1)));
    }
    if (verticals.size() == 0 || verticals[0]._center.x <= w_proc / 2) {
      verticals.push_back(Line(Point(w_proc - 1, 0), Point(w_proc - 1, h_proc - 1)));
    }
  }
  // sort lines according to their center point
  sort(horizontals.begin(), horizontals.end(), cmp_y);
  sort(verticals.begin(), verticals.end(), cmp_x);
  // for visualization only
  if (debug) {
    line(img_proc, horizontals[0]._p1, horizontals[0]._p2, Scalar(0, 255, 0), 2, CV_AA);
    line(img_proc, horizontals[horizontals.size() - 1]._p1, horizontals[horizontals.size() - 1]._p2, Scalar(0, 255, 0), 2, CV_AA);
    line(img_proc, verticals[0]._p1, verticals[0]._p2, Scalar(255, 0, 0), 2, CV_AA);
    line(img_proc, verticals[verticals.size() - 1]._p1, verticals[verticals.size() - 1]._p2, Scalar(255, 0, 0), 2, CV_AA);
  }

  /* perspective transformation */

  // define the destination image size: A4 - 200 PPI
  int w_a4 = 1654, h_a4 = 2339;
  //int w_a4 = 595, h_a4 = 842;
  Mat dst = Mat::zeros(h_a4, w_a4, CV_8UC3);

  // corners of destination image with the sequence [tl, tr, bl, br]
  vector<Point2f> dst_pts, img_pts;
  dst_pts.push_back(Point(0, 0));
  dst_pts.push_back(Point(w_a4 - 1, 0));
  dst_pts.push_back(Point(0, h_a4 - 1));
  dst_pts.push_back(Point(w_a4 - 1, h_a4 - 1));

  // corners of source image with the sequence [tl, tr, bl, br]
  img_pts.push_back(computeIntersect(horizontals[0], verticals[0]));
  img_pts.push_back(computeIntersect(horizontals[0], verticals[verticals.size() - 1]));
  img_pts.push_back(computeIntersect(horizontals[horizontals.size() - 1], verticals[0]));
  img_pts.push_back(computeIntersect(horizontals[horizontals.size() - 1], verticals[verticals.size() - 1]));

  // convert to original image scale
  for (size_t i = 0; i < img_pts.size(); i++) {
    // for visualization only
    if (debug) {
      circle(img_proc, img_pts[i], 10, Scalar(255, 255, 0), 3);
    }
    img_pts[i].x *= scale;
    img_pts[i].y *= scale;
  }

  // get transformation matrix
  Mat transmtx = getPerspectiveTransform(img_pts, dst_pts);

  // apply perspective transformation
  warpPerspective(img, dst, transmtx, dst.size());

  vector<Point> edges;
  // save dst img
  imwrite(dstFile, dst);
    {
        edges = getPoints(dst);
        if (edges.size() == 0) {
            printf("did not get edge points");
        } else {
            printf("did  get edge points");
        }
    }

  // for visualization only
  if (debug) {
//    namedWindow("dst", CV_WINDOW_KEEPRATIO);
//    imshow("src", img_dis);
//    imshow("canny", canny);
//    imshow("img_proc", img_proc);
//    imshow("dst", dst);
//    waitKey(0);
  }
	return edges;
}

//viren+
double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 ) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

vector<Point> getPoints(Mat image)
{
    int width = image.size().width;
    int height = image.size().height;
    Mat image_proc = image.clone();
    vector<vector<Point> > squares;
    // blur will enhance edge detection
    Mat blurred(image_proc);
    medianBlur(image_proc, blurred, 9);
    
    Mat gray0(blurred.size(), CV_8U), gray;
    vector<vector<Point> > contours;
    
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
                
                // Dilate helps to remove potential holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                gray = gray0 >= (l+1) * 255 / threshold_level;
            }
            
            // Find contours and store them in a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
            
            // Test contours
            vector<Point> approx;
            for (size_t i = 0; i < contours.size(); i++)
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
                
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if (approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx)))
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
        
        double largest_area = -1;
        int largest_contour_index = 0;
        for(int i=0;i<squares.size();i++)
        {
            double a =contourArea(squares[i],false);
            if(a>largest_area)
            {
                largest_area = a;
                largest_contour_index = i;
            }
        }
        
        //__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Scaning size() %d",squares.size());
        vector<Point> points;
        if(squares.size() > 0)
        {
            points = squares[largest_contour_index];
        }
        else
        {
            points.push_back(Point(0, 0));
            points.push_back(Point(width, 0));
            points.push_back(Point(0, height));
            points.push_back(Point(width, height));
        }
        
        return points;
    }
    
    //viren+
    vector<Point> dummyPoints;
    return dummyPoints;
    //viren-
}

Point2f computePoint(int p1, int p2) {
    Point2f pt;
    pt.x = p1;
    pt.y = p2;
    return pt;
}

//viren-

static int _pleaseScan(const char* path, const char* theOutputPath) {
    string thepath = path;
    string andtheOutputPath = theOutputPath;
    vector<Point> ret = scan(thepath, andtheOutputPath);
	return 0;
}

#ifdef __cplusplus
extern "C" {
#endif

int pleaseScan(const char* path, const char* theOutputPath) {
  _pleaseScan(path, theOutputPath);
  return 0;
}

#ifdef __cplusplus
}
#endif
