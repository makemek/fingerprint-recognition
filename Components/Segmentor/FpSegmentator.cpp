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
	bool background = average < 120 && stdDeviation < 30;
	bool finger = average >= 110 && stdDeviation < 35;
	return !(finger || background);
}

cv::Mat FpSegmentator::getMask(const cv::Mat & fpImg)
{
	cv::Mat mask = cv::Mat::zeros(fpImg.rows, fpImg.cols, CV_8UC1);

	int blockSize = 16;
	for (int row = 0; row < fpImg.rows; row += blockSize) {
		for (int col = 0; col < fpImg.cols; col += blockSize) {
			cv::Mat subSourceImg = fpImg(cv::Rect(col, row, blockSize, blockSize));
			if (hasFingerprintLine(subSourceImg)) {
				cv::Mat blockOfMask = cv::Mat(mask, cv::Rect(col, row, blockSize, blockSize));
				cv::Mat whiteMat = cv::Mat(blockSize, blockSize, CV_8UC1, cv::Scalar(255));
				blockOfMask += whiteMat; // assign white mask to mask's subblock
			}
		}
	}
	
	return mask;
}
//----------------------------------------------------------------------