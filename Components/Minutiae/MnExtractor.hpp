#ifndef MN_EXTRACTOR
#define MN_EXTRACTOR

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "MnSet.hpp"
using namespace std;

//----------------------------------------------------------------------
//Minutiae Extractor
//----------------------------------------------------------------------
class MnExtractor {
public:
   //constructors & destructor
   
   //getters & setters
   
   //key methods
   void extract(const cv::Mat& enhancedImg, MnSet& mnSet);
   void drawMinutiaes(const cv::Mat &img, const MnSet &coords, cv::Mat &output, const int &magnify = 1);
   
   //operators

private:
   //attributes
   
   //helper (private) methods
	void crossingNumber(const cv::Mat& input, cv::Mat& output);

};
//----------------------------------------------------------------------
#endif