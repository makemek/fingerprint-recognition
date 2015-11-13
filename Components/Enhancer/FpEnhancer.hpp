#ifndef FP_ENHANCER
#define FP_ENHANCER

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "GaborFilterbank.hpp"
#include "OfDetector.hpp"

using namespace std;

//----------------------------------------------------------------------
//Fingerprint (FP) Enhancer
//----------------------------------------------------------------------
class FpEnhancer {
public:
   //constructors & destructor
   
   //getters & setters
   
   //key methods
   cv::Mat enhance(const cv::Mat& segmentedFingerprintImg);
   
   //operators

private:
	GaborFilterbank gaborFilterBank;
	OfDetector OF_Field;
};
//----------------------------------------------------------------------
#endif