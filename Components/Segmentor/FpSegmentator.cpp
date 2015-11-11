#include "FpSegmentator.hpp"
#include <math.h>
//----------------------------------------------------------------------

cv::Mat FpSegmentator::segment(const cv::Mat & fpImg)
{
	cv::Mat segmentedImg = fpImg.clone();
	cv::bitwise_and(fpImg, getMask(fpImg), segmentedImg);
	return segmentedImg;
}

bool FpSegmentator::hasFingerprintLine(const cv::Mat& fpImgBlock) {
   
	assert(fpImgBlock.rows == fpImgBlock.cols);

	int totalPixelValue = 0, totalPixelSquareValue = 0;
	for (auto it = fpImgBlock.begin<uchar>(); it != fpImgBlock.end<uchar>(); ++it) {
		totalPixelValue += *it;
		totalPixelSquareValue += pow(*it, 2);
	}
	
	double average = 0, stdDeviation = 0;
	int nPixel = fpImgBlock.rows * fpImgBlock.cols;
	average = (double)totalPixelValue / nPixel;
	stdDeviation = sqrt(totalPixelSquareValue / nPixel - pow(average, 2));
	
	cout << "avg " << average << ' ' << "std " << stdDeviation << endl;
	return average < 40 && stdDeviation < 60;
}

cv::Mat FpSegmentator::getMask(const cv::Mat & fpImg)
{

	throw exception("Not implemented");
	if (hasFingerprintLine(fpImg))
		return cv::Mat::zeros(cv::Size(fpImg.rows, fpImg.cols), CV_8U);
	
}
//----------------------------------------------------------------------