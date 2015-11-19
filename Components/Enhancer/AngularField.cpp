#include "AngularField.hpp"
#include "opencv2\imgproc\imgproc.hpp"

AngularField::AngularField(const cv::Mat & mat)
{
	this->ang = mat;
}

cv::Mat AngularField::visualize(const cv::Size& blockSize)
{
	cv::Mat visual = cv::Mat::zeros(ang.rows * blockSize.height, ang.cols * blockSize.width, CV_8UC1);

	auto it = ang.begin<float>();

	for (int i = 0; i <= visual.rows - blockSize.height; i += blockSize.height)
	{
		for (int j = 0; j <= visual.cols - blockSize.width; j += blockSize.width)
		{
			float dx = blockSize.width*cos(*it);
			float dy = blockSize.height*sin(*it);
			int x = j;
			int y = i;

			cv::line(visual, cv::Point(x, y), cv::Point(x + dx, y + dy), cv::Scalar::all(255), 1, CV_AA);

			++it;
		}
	}

	return visual;
	
}

cv::Mat AngularField::getAngularMatrix()
{
	return ang;
}
