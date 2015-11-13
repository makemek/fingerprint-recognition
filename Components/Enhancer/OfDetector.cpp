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

float OfDetector::estimateAngle(const cv::Mat& gx, const cv::Mat& gy) {
	double a = 0, b = 0;
	assert(gx.size == gy.size);

	auto it_gx = gx.begin<float>(), it_gy = gy.begin<float>();
	while(it_gx != gx.end<float>()) {
		double gxVal = *it_gx;
		double gyVal = *it_gy;

		a += 2 * gxVal*gyVal;
		b += pow(gxVal, 2)*pow(gyVal, 2);

		++it_gx;
		++it_gy;
	}

	if (b == 0)
		return 0;

	return a / b;
}

//----------------------------------------------------------------------
/*
fpImg image input
ofImg output image with oriental field estimation
*/
cv::Mat OfDetector::detect(cv::Size kSize, const cv::Mat& img) { 

   cout << "Stub: orietation field (OF) detection" << endl; 

   cv::Mat thinned;

   thinned = img.clone();
   cv::Mat gx, gy, ang, mag;
   cv::Sobel(thinned, gx, CV_32FC1, 1, 0, 7);
   cv::Sobel(thinned, gy, CV_32FC1, 0, 1, 7);
   cv::phase(gx, gy, ang, false);
   cv::magnitude(gx, gy, mag);

   cv::normalize(mag, mag, 0, 1, cv::NORM_MINMAX);

   cv::Mat angRes = cv::Mat::zeros(img.rows/kSize.height, img.cols/kSize.width, CV_32FC1);

   
   for (int i = 0; i <= img.rows - kSize.height; i += kSize.height)
   {
	   for (int j = 0; j <= img.cols - kSize.width; j += kSize.width)
	   {
		   cv::Rect roi = cv::Rect(i, j, kSize.width, kSize.height);
		   cv::Mat subMag = cv::Mat(mag, roi);
		   cv::Mat subAng = cv::Mat(ang, roi);
		   double theta = getWeightedAngle(subMag, subAng);
		   
		   angRes.at<float>(j / kSize.width, i / kSize.height) = theta;
	   }
   }

   return angRes;


}
//----------------------------------------------------------------------