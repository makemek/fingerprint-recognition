#ifndef ANGULAR_FIELD
#define ANGULAR_FIELD
#include "opencv2/core/core.hpp"

class AngularField {

public:
	AngularField(const cv::Mat& angleMat);

	cv::Mat visualize(const cv::Size& dimension);
	cv::Mat visualize(int width, int height);
	cv::Mat getAngularMatrix();

private:
	cv::Mat ang;
};

#endif
