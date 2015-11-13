#include "FpEnhancer.hpp"

cv::Mat FpEnhancer::enhance(const cv::Mat & fingerprintImg)
{
	cv::Mat angularField = OF_Field.detect(fingerprintImg);
	throw std::logic_error("Not implemented");
}
