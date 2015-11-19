#ifndef ANGULAR_FIELD
#define ANGULAR_FIELD
#include "opencv2/core/core.hpp"

class AngularField {

public:
	AngularField(const cv::Size& size, const cv::Mat& angleMat);
	AngularField(const cv::Mat& mat);

	cv::Mat visualize();
	cv::Mat getAngularMatrix();
	cv::Size getSize();

private:
	cv::Size size;
	cv::Mat mat;
};

#endif
