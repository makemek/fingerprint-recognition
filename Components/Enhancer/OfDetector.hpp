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
   cv::Mat detect(const cv::Mat& fpImg);
   
   //operators

private:
   //attributes
   
   //helper (private) methods
	float getWeightedAngle(cv::Mat& mag, cv::Mat& ang);
};
//----------------------------------------------------------------------
#endif