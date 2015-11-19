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

// algorithm from equation 4,5,6 http://arresearchpublication.com/images/shortpdf/1433002339_293.pdf
float OfDetector::estimateAngle(const cv::Mat& gx, const cv::Mat& gy) {
	double a = 0, b = 0;
	assert(gx.size == gy.size);

	int i = gx.cols / 2, j = gx.rows / 2;
	int w = gx.rows; // block size

	for (int u = i - w / 2; u < i + w / 2; ++u) {
		for (int v = j - w / 2; v < j + w / 2; ++v) {
			//double gxVal = gx.at<float>(i, j);
			//double gyVal = gy.at<float>(i, j);

			a += 2 * gx.at<uchar>(i, j)*gy.at<uchar>(i, j);
			b += pow(gx.at<uchar>(u, v), 2) - pow(gy.at<uchar>(u, v), 2);
		}
	}

	if (b == 0)
		return 0;

	return atan(b / a) / 2; // least square estimate
}

//----------------------------------------------------------------------
/*
fpImg image input
ofImg output image with oriental field estimation
*/
cv::Mat OfDetector::detect(cv::Size kSize, const cv::Mat& img) {

	cout << "Stub: orietation field (OF) detection" << endl;

	cv::Mat gx, gy, ang, mag;
	cv::Sobel(img, gx, CV_32FC1, 1, 0, 7);
	cv::Sobel(img, gy, CV_32FC1, 0, 1, 7);
	cv::phase(gx, gy, ang, false);
	cv::magnitude(gx, gy, mag);

	cv::normalize(mag, mag, 0, 1, cv::NORM_MINMAX);

	cv::Mat angRes = cv::Mat::zeros(img.rows / kSize.height, img.cols / kSize.width, CV_32FC1);

	for (int i = 0; i <= img.rows - kSize.height; i += kSize.height)
	{
		for (int j = 0; j <= img.cols - kSize.width; j += kSize.width)
		{
			cv::Rect roi = cv::Rect(j, i, kSize.width, kSize.height);
			cv::Mat subMag = cv::Mat(mag, roi);
			cv::Mat subAng = cv::Mat(ang, roi);
			float theta = getWeightedAngle(mag(cv::Rect(j, i, kSize.width, kSize.height)), ang(cv::Rect(j, i, kSize.width, kSize.height)));

			angRes.at<float>(i / kSize.height, j / kSize.width) = theta;
		}
	}

	return angRes;


}
cv::Mat OfDetector::drawField(const cv::Mat & srcImg, const cv::Mat & angle)
{
	cv::Size blockSize = cv::Size(srcImg.rows / angle.rows, srcImg.cols / angle.cols);

	cv::Mat visual = cv::Mat(srcImg.rows, srcImg.cols, CV_8UC1);

	auto it = angle.begin<float>();

	for (int i = 0; i <= srcImg.rows - blockSize.height; i += blockSize.height)
	{
		for (int j = 0; j <= srcImg.cols - blockSize.width; j += blockSize.width)
		{
			float dx = blockSize.width*cos(*it);
			float dy = blockSize.height*sin(*it);
			int x = j;
			int y = i;

			cv::line(visual, cv::Point(x, y), cv::Point(x + dx, y + dy), cv::Scalar::all(255), 1, CV_AA);

			++it;
		}
	}

	return visual;
}
//----------------------------------------------------------------------