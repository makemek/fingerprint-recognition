#ifndef OF_DETECTOR
#define OF_DETECTOR

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;

//----------------------------------------------------------------------
//Orientation Field (OF) Detector
//----------------------------------------------------------------------
class OfDetector {
public:
   //constructors & destructor
   
   //getters & setters
   
   //key methods
   cv::Mat detect(cv::Size kSize, const cv::Mat& fpImg);
   
   //operators

private:
   //attributes
   
   //helper (private) methods
	float getWeightedAngle(cv::Mat& mag, cv::Mat& ang);
	float estimateAngle(const cv::Mat& gx, const cv::Mat& gy);
};
//----------------------------------------------------------------------
#endif