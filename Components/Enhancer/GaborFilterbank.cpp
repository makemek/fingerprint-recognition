#include "GaborFilterbank.hpp"

//----------------------------------------------------------------------
cv::Mat GaborFilterbank::filter(const cv::Mat& fpImg, const cv::Mat& ofImg) { 

   cout << "Stub: apply Gabor filterbank to image" << endl;
   
   cv::Mat fpImgFloat;
   fpImg.convertTo(fpImgFloat, CV_32F);
   cv::Mat outImg = cv::Mat::zeros(fpImgFloat.rows, fpImgFloat.cols, fpImgFloat.type());
   //outImg.convertTo(outImg, CV_8U);

   cv::Size block = cv::Size(ofImg.rows, ofImg.cols);

   int row = 0, col = 0;
   auto it = ofImg.begin<float>();

   while (row < fpImg.rows) {
	   while (col < fpImg.cols) {
		   
		   double theta = quantize(8, *it);

		   double sig = 2, th = theta, lm = 1, gm = 3, ps = 0;
		   cv::Size kSize = cv::Size(31,31);
		   cv::Mat gaborFilter = cv::getGaborKernel(kSize, 1, th, lm, gm, ps);

		   cv::Rect roi = cv::Rect(col, row, block.width, block.height);
		   cv::Mat subFingerprintImg = cv::Mat(fpImgFloat,roi);
		   cv::Mat subOutImg = cv::Mat(outImg, roi);

		   cv::Mat gaborBlock;
		   cv::filter2D(subFingerprintImg, gaborBlock, CV_32F, gaborFilter);
		   gaborBlock.copyTo(subOutImg);

		   col += block.width;
		   ++it;
	   }
	   col = 0;
	   row += block.height;
   }
 
   outImg.convertTo(outImg, CV_8U);

   return outImg;
}

double GaborFilterbank::quantize(int directions, double angleRad)
{
	bool inverse = false;
	if (angleRad < 0)
		inverse = true;
	angleRad = abs(angleRad);
		
	double incrementAngle = CV_PI / directions;
	int atDirection = int(angleRad / incrementAngle);

	double quantizeAngle = incrementAngle * atDirection;
	double leftOver = abs(angleRad - quantizeAngle);

	if (leftOver >= incrementAngle / 2)
		quantizeAngle += incrementAngle; // round up to next direction

	if (inverse)
		quantizeAngle = -quantizeAngle;

	return quantizeAngle;
}
//----------------------------------------------------------------------