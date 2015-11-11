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
   void segment(const cv::Mat& fpImg, cv::Mat& maskImg);

   //operators

private:
   //attributes
	const static int FP_AREA = 0;
	const static int NON_FP_AREA = 255;

	const static int BLOCK_SIZE = 16;
   
   //helper (private) methods
   
};
//----------------------------------------------------------------------
#endif