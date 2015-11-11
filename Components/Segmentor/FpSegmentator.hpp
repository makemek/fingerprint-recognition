#ifndef FP_SEGMENTATOR
#define FP_SEGMENTATOR

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;

//----------------------------------------------------------------------

//----------------------------------------------------------------------
//Fingerprint (FP) Segmentator
//----------------------------------------------------------------------
class FpSegmentator {
public:
   //constructors & destructor
   
   //getters & setters
   
   //key methods

	/*
	Extract 
	*/
	cv::Mat segment(const cv::Mat& fpImg);

	/*
	Check if image has finger print presents
	*/
	bool hasFingerprintLine(const cv::Mat& fpImgBlock);

	cv::Mat getMask(const cv::Mat& fpImg);

private:
   //attributes
	const int FP_AREA = 0;
	const int NON_FP_AREA = 255;

	int block_size;
   
   //helper (private) methods
   
};
//----------------------------------------------------------------------
#endif