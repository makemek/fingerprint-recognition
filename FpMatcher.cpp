#include "FpMatcher.hpp"
#include "OfDetector.hpp"
//----------------------------------------------------------------------
double FpMatcher::match(const cv::Mat& fpImg1, const cv::Mat& fpImg2) { 

   cout << "Stub: matching fpImg1 with fpImg2" << endl; 
   
   // segmentation
   //cv::threshold(fpImg1, fpImg1, 128, 255, cv::THRESH_BINARY);
   //cv::threshold(fpImg2, fpImg2, 128, 255, cv::THRESH_BINARY);

   OfDetector ofDetector = OfDetector();
   cv::imshow("1", ofDetector.detect(fpImg1));
   //cv::imshow("2", ofDetector.detect(fpImg2));

   return 100.0; 
}
//----------------------------------------------------------------------