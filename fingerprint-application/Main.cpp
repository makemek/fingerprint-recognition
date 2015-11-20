#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "FpSegmentator.hpp"
#include "FpMatcher.hpp"
#include "Skeletonizer.hpp"
using namespace std;
//----------------------------------------------------------------------

/*
To compile this program you need to 
    1. Create environment variable call "opencv" points to (Your opencv installation path)\build\x86\vc12
	2. Add %opencv%\bin to PATH environment variable
	
To run this program, you have to 
    1. put 2 command line argument containing path to an image
		1.1. path to input fingerprint image
		1.2. path to fingerprint template image
*/
int main(int argc, char** argv) {
	assert(argc == 3);

   //read fingerprint image 1
   cv::Mat fpImg1 = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

   //read fingerprint image 2
   cv::Mat fpImg2 = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
   
   assert(fpImg1.data && fpImg2.data);

   cv::imshow("fingerprint1", fpImg1);
   cv::imshow("fingerprint2", fpImg2);

   //match two fingerprint images
   //FpMatcher fpMatcher;
   //double similarity = fpMatcher.match(fpImg1, fpImg2);
   //cout << "Similarity = " << similarity << endl;

   FpSegmentator segmentor = FpSegmentator();
   FpEnhancer enhancer = FpEnhancer();

   cv::Mat segImg = segmentor.segment(fpImg1);
   cv::imshow("segmented", segImg);

   cv::Mat enhImg = enhancer.enhance(segImg);
   cv::imshow("Enhanced", enhImg);

   cv::Mat skeletonImg;
   Skeletonizer::skeletonize(enhImg, skeletonImg);
   cv::imshow("Skeletonized", skeletonImg);

   cv::waitKey();
}
//----------------------------------------------------------------------