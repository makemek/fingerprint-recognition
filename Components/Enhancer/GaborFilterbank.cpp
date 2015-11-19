#include "GaborFilterbank.hpp"

//----------------------------------------------------------------------
cv::Mat GaborFilterbank::filter(const cv::Size& blockSize, const cv::Mat& fpImg, const cv::Mat& ofImg) {

   cout << "Stub: apply Gabor filterbank to image" << endl;
   
   cv::Mat fpImgFloat;
   fpImg.convertTo(fpImgFloat, CV_32F);
   cv::Mat outImg = cv::Mat::zeros(fpImgFloat.rows, fpImgFloat.cols, fpImgFloat.type());
   //outImg.convertTo(outImg, CV_8U);

   int row = 0, col = 0;
   auto it = ofImg.begin<float>();
   const int KSIZE = 21;

   while (row < fpImg.rows) {
	   while (col < fpImg.cols) {
		   
		   int direction = 8;
		   
		   double theta = quantize(direction, *it * 180/CV_PI);
		   
		   double sig = 5, th = *it * 180 / CV_PI, lm = 0.5 + 50 / 100.0, ps = 90;
		   
		   cv::Mat gaborFilter = this->getGaborKernel(KSIZE, sig, th + 90, lm, ps);

		   cv::Rect roi = cv::Rect(col, row, blockSize.width, blockSize.height);
		   cv::Mat subFingerprintImg = cv::Mat(fpImgFloat,roi);
		   cv::Mat subOutImg = cv::Mat(outImg, roi);
		   cv::Mat gaborBlock;
		   cv::filter2D(subFingerprintImg, gaborBlock, CV_32F, gaborFilter);
		   gaborBlock.copyTo(subOutImg);

		   col += blockSize.width;
		   ++it;
	   }
	   col = 0;
	   row += blockSize.height;
   }
 
   outImg.convertTo(outImg, CV_8U);

   return outImg;
}

cv::Mat GaborFilterbank::getGaborKernel(int ks, double sig, double th, double lm, double ps) {
	int hks = (ks - 1) / 2;
	double theta = th*CV_PI / 180;
	double psi = ps*CV_PI / 180;
	double del = 2.0 / (ks - 1);
	double lmbd = lm;
	double sigma = sig / ks;
	double x_theta;
	double y_theta;
	cv::Mat kernel(ks, ks, CV_32F);
	for (int y = -hks; y <= hks; y++)
	{
		for (int x = -hks; x <= hks; x++)
		{
			x_theta = x*del*cos(theta) + y*del*sin(theta);
			y_theta = -x*del*sin(theta) + y*del*cos(theta);
			kernel.at<float>(hks + y, hks + x) = (float)exp(-0.5*(pow(x_theta, 2) + pow(y_theta, 2)) / pow(sigma, 2))* cos(2 * CV_PI*x_theta / lmbd + psi);
		}
	}
	return kernel;
}

double GaborFilterbank::quantize(int directions, double angle)
{
	bool inverse = false;
	if (angle < 0)
		inverse = true;
	angle = abs(angle);
		
	double incrementAngle = 360.0/2 / directions;
	int atDirection = int(angle / incrementAngle);

	double quantizeAngle = incrementAngle * atDirection;
	double boundary = incrementAngle / 2 + quantizeAngle /* shift up */;
	double leftOver = angle - boundary;

	if (leftOver > 0)
		quantizeAngle += incrementAngle; // round up to next direction

	if (inverse)
		quantizeAngle = -quantizeAngle;

	//cout << angle << ' ' << quantizeAngle << endl;

	return quantizeAngle;
}
//----------------------------------------------------------------------