#include "FpEnhancer.hpp"

cv::Mat FpEnhancer::enhance(const cv::Mat & fingerprintImg)
{
	AngularField angularField = OF_Field.detect(cv::Size(16,16), fingerprintImg);
	cv::Mat filtered = gaborFilterBank.filter(fingerprintImg, angularField.getAngularMatrix());
	
	return filtered;
}
