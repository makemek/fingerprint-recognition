#ifndef GABOR_FILTER
#define GABOR_FILTER

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;

//----------------------------------------------------------------------
//Gabor filter
//----------------------------------------------------------------------
class GaborFilter : public cv::Mat {
public:
   //constructors & destructor
   GaborFilter(cv::Size size, double orientVal, double freqVal);
   
   //getters & setters
   
   //key methods

   //operators

private:
   //attributes
  
   //helper (private) methods
   
};
//----------------------------------------------------------------------
#endif