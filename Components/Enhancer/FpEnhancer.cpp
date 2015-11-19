#include "FpEnhancer.hpp"

cv::Mat FpEnhancer::enhance(const cv::Mat & fingerprintImg)
{
	cv::Size divBlock = cv::Size(16, 16);
	AngularField angularField = OF_Field.detect(divBlock, fingerprintImg);
	cv::Mat filtered = gaborFilterBank.filter(divBlock, fingerprintImg, angularField.getAngularMatrix());
	
	return filtered;
}
