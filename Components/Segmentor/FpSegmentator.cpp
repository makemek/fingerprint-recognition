#include "FpSegmentator.hpp"
#include <math.h>
//----------------------------------------------------------------------

cv::Mat FpSegmentator::segment(const cv::Mat & fpImg)
{
	cv::Mat biImg;
	cv::Mat maskImg = fpImg.clone();

	cv::threshold(fpImg, biImg, 128, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
	bool isFinger;

	for (int i = 0; i < maskImg.rows; i++) {
		isFinger = false;
		for (int j = 0; j <= maskImg.cols / 2; j++) {
			if (biImg.at<uchar>(i, j) == 0 && !isFinger) {
				maskImg.at<uchar>(i, j) = 255;
			}
			else if (biImg.at<uchar>(i, j) != 0) {
				isFinger = true;
				maskImg.at<uchar>(i, j) = 255;
			}
		}
	}

	for (int x = 0; x < maskImg.rows; x++) {
		isFinger = false;
		for (int y = maskImg.cols - 1; y > maskImg.cols / 2; y--) {
			if (biImg.at<uchar>(x, y) == 0 && !isFinger) {
				maskImg.at<uchar>(x, y) = 255;
			}
			else if (biImg.at<uchar>(x, y) != 0) {
				isFinger = true;
				maskImg.at<uchar>(x, y) = 255;
			}
		}
	}

	return biImg;
}

bool FpSegmentator::hasFingerprintLine(const cv::Mat& fpImgBlock) {
   
	assert(fpImgBlock.rows == fpImgBlock.cols);

	int totalPixelValue = 0, totalPixelSquareValue = 0;
	for (auto it = fpImgBlock.begin<uchar>(); it != fpImgBlock.end<uchar>(); ++it) {
		totalPixelValue += *it;
		totalPixelSquareValue += *it * *it;
	}
	
	double average = 0, stdDeviation = 0;
	int nPixel = fpImgBlock.rows * fpImgBlock.cols;
	average = (double)totalPixelValue / nPixel;
	stdDeviation = sqrt(totalPixelSquareValue / nPixel - pow(average, 2));
	
	bool background = average < 120 && stdDeviation < 20;
	return !background;
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