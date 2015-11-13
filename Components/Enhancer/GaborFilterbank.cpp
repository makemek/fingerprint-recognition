#include "GaborFilterbank.hpp"

//----------------------------------------------------------------------
cv::Mat GaborFilterbank::filter(const cv::Mat& fpImg, const cv::Mat& ofImg) { 

	throw std::logic_error("Not implemented");

   cout << "Stub: apply Gabor filterbank to image" << endl; 
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