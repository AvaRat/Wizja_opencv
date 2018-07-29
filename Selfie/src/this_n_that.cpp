/*
 * this_n_that.cpp
 *
 *  Created on: 17 maj 2018
 *      Author: marcel
 */

#include "this_n_that.hpp"

#include"imgproc.hpp"
#include"core.hpp"
#include"highgui.hpp"
#include"videoio.hpp"
#include"core/types_c.h"
#include<vector>
#include<iostream>

using namespace std;
using namespace cv;

const Vec4i colors[7] = {
		Scalar(255,0,0), Scalar(0,0,255), Scalar(0,255,0),
		Scalar(0,255,255), Scalar(255,0,210), Scalar(255,255,255), Scalar(0,0,0)
};

/*
void sort_lines(vector<Vec4i> &v)
{
	Vec4i* lines_values[v.size()];
	unsigned i;
	int line_x_center;

	//abs(l[0]-l[2])/2;

}
void vecToArray(vector<Vec4i> &v, Vec4i **array)
{
	for(unsigned i=0;  i<v.size();  i++)
		array[i] = v[i];
}
*/



double get_x_center(Mat &src, Mat &target, int threshold, cl color)
{
	vector<Vec4i> p_lines;

	HoughLinesP(src, p_lines, 1, CV_PI / 180, threshold, 30, 10);
	double sum_left = 0, sum_right = 0;
	double num_left = 0, num_right = 0;
	size_t i;
	for (i = 0; i < p_lines.size(); i++)
	{
		Vec4i l = p_lines[i];
		line(target, Point(l[0], l[1]), Point(l[2], l[3]), colors[color], 3,
				LINE_AA);
		double x = (l[0] + l[2]) / 2;
		if (x < src.cols / 2)
		{
			sum_left += x;
			num_left++;
		} else
		{
			sum_right += x;
			num_right++;
		}
	}
	double avg_x_left = sum_left / num_left;
	double avg_x_right = sum_right / num_right;
	double center = (avg_x_left + avg_x_right) / 2;
	line(target, Point(center, target.rows), Point(center, 0), colors[red], 10,
			LINE_AA);
	//cout << p_lines.size() <<endl;

	return center;
}
double get_x_center(Mat &src, Mat &target, int threshold, cl color, vector<Vec4i> *v)
{
	vector<Vec4i> p_lines;

	HoughLinesP(src, p_lines, 1, CV_PI / 180, threshold, 30, 10);
	*v = p_lines;
	double sum_left = 0, sum_right = 0;
	double num_left = 0, num_right = 0;
	size_t i;
	for (i = 0; i < p_lines.size(); i++)
	{
		Vec4i l = p_lines[i];
		line(target, Point(l[0], l[1]), Point(l[2], l[3]), colors[color], 3,
				LINE_AA);
		double x = (l[0] + l[2]) / 2;
		if (x < src.cols / 2)
		{
			sum_left += x;
			num_left++;
		} else
		{
			sum_right += x;
			num_right++;
		}
	}
	double avg_x_left = sum_left / num_left;
	double avg_x_right = sum_right / num_right;
	double center = (avg_x_left + avg_x_right) / 2;
	line(target, Point(center, target.rows), Point(center, 0), colors[red], 10,
			LINE_AA);
	cout << p_lines.size() <<endl;

	return center;

}

void filtr(Mat &src, Mat &target)
{
	Mat kernel = (Mat_<char>(3, 3) << 0, 0, 0, 1, 0, -1, 0, 0, 0);
	filter2D(src, target, -1, kernel);
}




