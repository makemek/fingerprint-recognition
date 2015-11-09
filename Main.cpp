#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "FpSegmentator.hpp"
#include "FpMatcher.hpp"
using namespace std;

//----------------------------------------------------------------------
int main() {
   //read fingerprint image 1
   cv::Mat fpImg1 = cv::imread("FP_DB/1_1.bmp", CV_LOAD_IMAGE_GRAYSCALE);
   cv::imshow("fp1", fpImg1);

   //read fingerprint image 2
   cv::Mat fpImg2 = cv::imread("FP_DB/1_1.bmp", CV_LOAD_IMAGE_GRAYSCALE);
   cv::imshow("fp2", fpImg1);

   //match two fingerprint images
   FpMatcher fpMatcher;
   double similarity = fpMatcher.match(fpImg1, fpImg2);
   cout << "Similarity = " << similarity << endl;

   cv::waitKey();
}
//----------------------------------------------------------------------