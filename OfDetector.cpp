#include "OfDetector.hpp"
#include <stdarg.h>
#include <math.h>

float OfDetector::getWeightedAngle(cv::Mat& mag, cv::Mat& ang)
{
	float res = 0;
	float n = 0;
	for (int i = 0; i< mag.rows; ++i)
	{
		for (int j = 0; j< mag.cols; ++j)
		{
			res += ang.at<float>(i, j)*mag.at<float>(i, j);
			n += mag.at<float>(i, j);
		}
	}

	

	if (n == 0)
		return 0;

	res /= n;
	return res;
}

//----------------------------------------------------------------------
/*
fpImg image input
ofImg output image with oriental field estimation
*/
cv::Mat OfDetector::detect(const cv::Mat& img) { 

   cout << "Stub: orietation field (OF) detection" << endl; 

   cv::Mat thinned;

   thinned = img.clone();
   cv::Mat gx, gy, ang, mag;
   cv::Sobel(thinned, gx, CV_32FC1, 1, 0, 7);
   cv::Sobel(thinned, gy, CV_32FC1, 0, 1, 7);
   cv::phase(gx, gy, ang, false);
   cv::magnitude(gx, gy, mag);

   cv::normalize(mag, mag, 0, 1, cv::NORM_MINMAX);


   cv::Mat angRes = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);

   int blockSize = img.cols / 25 - 1;
   float r = blockSize;

   for (int i = 0; i< img.rows - blockSize; i += blockSize)
   {
	   for (int j = 0; j< img.cols - blockSize; j += blockSize)
	   {

		   float a = getWeightedAngle(mag(cv::Rect(j, i, blockSize, blockSize)), ang(cv::Rect(j, i, blockSize, blockSize)));
		   //cout << a << endl; 
		   float dx = r*cos(a);
		   float dy = r*sin(a);
		   int x = j;
		   int y = i;

		   cv::line(angRes, cv::Point(x, y), cv::Point(x + dx, y + dy), cv::Scalar::all(255), 1, CV_AA);
	   }
   }
   
   return angRes;


}
//----------------------------------------------------------------------