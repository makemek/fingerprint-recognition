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
			cv::Mat src = cv::imread("C:\\Users\\Apipol\\Desktop\\FP_DB\\1_2.BMP");
			OfDetector detector = OfDetector();
			cv::Mat field = detector.detect(cv::Size(16,16), src);
			cv::imshow("out", field);
			cv::waitKey();
		}

	};
}