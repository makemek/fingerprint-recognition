#ifndef GABOR_FILTERBANK
#define GABOR_FILTERBANK

#include <iostream>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "OfDetector.hpp"

using namespace std;


/**Gabor filterbank
A collection of Gabor filter
*/
class GaborFilterbank {
public:

	/**
	
	*/
	cv::Mat filter(const cv::Mat& fingerprintImg, const cv::Mat& orientalFieldImg);

private:
   vector<cv::Mat> gbs;
};
//----------------------------------------------------------------------
#endif