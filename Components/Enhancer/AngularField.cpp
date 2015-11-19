#include "AngularField.hpp"
#include "opencv2\imgproc\imgproc.hpp"

AngularField::AngularField(const cv::Mat & mat)
{
	this->ang = mat;
}

cv::Mat AngularField::visualize(const cv::Size& dimension)
{
	return visualize(dimension.width, dimension.height);
}

cv::Mat AngularField::visualize(int width, int height)
{
	const int stepX = width / ang.cols;
	const int stepY = height / ang.rows;
	cv::Mat visual = cv::Mat::zeros(height, width, CV_8UC1);

	auto it = ang.begin<float>();

	for (int i = 0; i <= visual.rows - stepY; i += stepY)
	{
		for (int j = 0; j <= visual.cols - stepX; j += stepX)
		{
			float dx = stepX*cos(*it);
			float dy = stepY*sin(*it);
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
