#include "MnExtractor.hpp"

//----------------------------------------------------------------------
void MnExtractor::crossingNumber(const cv::Mat& input, cv::Mat& output)
{
	// 1. Create a replication of an input "image" with only 0s and 1s
	int i, j;
	output = cv::Mat::zeros(input.size(), CV_8U);
	cv::Mat tempInput = cv::Mat::zeros(input.size(), CV_8U);

	for (i = 0; i < input.rows; ++i)
	{
		for (j = 0; j < input.cols; ++j)
		{
			if (input.at<uchar>(i, j) > 0)
				tempInput.at<uchar>(i, j) = 1;
		}
	}

	// 2. Perform a formula for obtaining a crossing number
	for (i = 1; i < input.rows - 1; ++i)
	{
		for (j = 1; j < input.cols - 1; ++j)
		{
			if (input.at<uchar>(i, j) > 0)
			{
				output.at<uchar>(i, j) = (
					abs(tempInput.at<uchar>(i - 1, j - 1) - tempInput.at<uchar>(i - 1, j)) +
					abs(tempInput.at<uchar>(i - 1, j) - tempInput.at<uchar>(i - 1, j + 1)) +
					abs(tempInput.at<uchar>(i - 1, j + 1) - tempInput.at<uchar>(i, j + 1)) +
					abs(tempInput.at<uchar>(i, j + 1) - tempInput.at<uchar>(i + 1, j + 1)) +
					abs(tempInput.at<uchar>(i + 1, j + 1) - tempInput.at<uchar>(i + 1, j)) +
					abs(tempInput.at<uchar>(i + 1, j) - tempInput.at<uchar>(i + 1, j - 1)) +
					abs(tempInput.at<uchar>(i + 1, j - 1) - tempInput.at<uchar>(i, j - 1)) +
					abs(tempInput.at<uchar>(i, j - 1) - tempInput.at<uchar>(i - 1, j - 1))) / 2;
			}
		}
	}
}
//----------------------------------------------------------------------
void MnExtractor::extract(const cv::Mat& enhancedImg, MnSet& mnSet) { 
   
	// 1. Preparation
   cout << "Stub: minutaie extraction" << endl; 

   cv::Mat crossNum;
   Minutiae temp;
   int i, j;

   // 2. Obtain a crossing number map for minutiae detection
   crossingNumber(enhancedImg, crossNum);

   // 3. Find all pixels where crossing number is 0, 1, or 3
   for (i = 1; i < crossNum.rows - 1; ++i)
   {
	   for (j = 1; j < crossNum.cols - 1; ++j)
	   {
		   // Crossing Number 0 is an unknown minutiae
		   if (crossNum.at<uchar>(i, j) == 0)
		   {
			   temp.pos.x = i;
			   temp.pos.y = j;
			   temp.type = M_TYPE_UNKNOWN;
			   mnSet.push_back(temp);
		   }
		   // Crossing Number 0 is an endpoint minutiae
		   else if (crossNum.at<uchar>(i, j) == 1)
		   {
			   temp.pos.x = i;
			   temp.pos.y = j;
			   temp.type = M_TYPE_ENDPOINT;
			   mnSet.push_back(temp);
		   }
		   // Crossing Number 0 is a bifurication minutiae
		   else if (crossNum.at<uchar>(i, j) == 3)
		   {
			   temp.pos.x = i;
			   temp.pos.y = j;
			   temp.type = M_TYPE_BIFURCATION;
			   mnSet.push_back(temp);
		   }
	   }
   }
}
//----------------------------------------------------------------------
void MnExtractor::drawMinutiaes(const cv::Mat &img, const MnSet &coords, cv::Mat &output, const int &magnify)
{
	cv::resize(img, output, img.size() * magnify);
	int i;

	for (int i = 0; i < coords.size(); ++i)
	{
		if(coords[i].type != M_TYPE_UNKNOWN)
			cv::circle(output, cv::Point(coords[i].pos.y, coords[i].pos.x) * magnify, magnify + 5, 128);
	}
}
//----------------------------------------------------------------------