#ifndef ANGULAR_FIELD
#define ANGULAR_FIELD
#include "opencv2/core/core.hpp"

class AngularField {

public:
	AngularField(const cv::Mat& angleMat);

	cv::Mat visualize(const cv::Size& blockSize);
	cv::Mat getAngularMatrix();

private:
	cv::Mat ang;
};

#endif
