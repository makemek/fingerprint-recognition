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
			Assert::IsTrue(src.data);

			OfDetector detector = OfDetector();
			AngularField field = detector.detect(cv::Size(8,8), src);
			
			cv::Size size = cv::Size(256, 256);
			cv::Mat visual = field.visualize(size);

			Assert::AreEqual(size.height, visual.rows);
			Assert::AreEqual(size.width, visual.cols);

			cv::imshow("out", field.visualize(256,256));
			cv::waitKey();
		}

	};
}