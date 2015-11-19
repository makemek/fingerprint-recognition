#include "stdafx.h"
#include "CppUnitTest.h"
#include "OfDetector.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EnhancerTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestOrientalFieldDetector)
		{
			cv::Mat src = cv::imread("C:\\Users\\Make\\Desktop\\FP_DB\\1_1.BMP");
			OfDetector detector = OfDetector();
			cv::Mat field = detector.detect(cv::Size(8,8), src);
			cv::Mat out = detector.drawField(src, field);
			cv::imshow("out", out);
			cv::waitKey();
		}

	};
}