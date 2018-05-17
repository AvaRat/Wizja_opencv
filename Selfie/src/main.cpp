#include"imgproc.hpp"
#include"core.hpp"
#include"highgui.hpp"
#include"videoio.hpp"
#include<iostream>
#include<cmath>
#include"this_n_that.hpp"

#define CHECK(x) if(!x.data){	std::cout << "nie ma nic w srodku!!\n"; return -1;}else std::cout<<"ok\n";

using namespace std;
using namespace cv;

/// Function Headers
void filtr(Mat&, Mat&);
double get_x_center(Mat &src, Mat &img, int, cl);

/**
 * @function main
 */
int main(int argc, char** argv) {
	Mat src;
	Mat temp, temp2, temp3, target;

	if (argc == 2) {
		VideoCapture cap(1);
		if (!cap.isOpened()) {
			cout << "nie mozna odczytac z kamery\n";
			return -1;
		}

		for (;;) {
			cap >> src;
			target = src;
			cvtColor(src, temp, COLOR_RGB2GRAY);
			Canny(temp, temp3, 50, 200);
			namedWindow("after Canny without filter", 0);
			imshow("after Canny without filter", temp3);
			get_x_center(temp3, target, 100, blue); //niebieski
			namedWindow("after transformations", WINDOW_NORMAL);
			imshow("after transformations", target);
			if (waitKey(30) >= 0)
				break;
		}
		return 0;
		//end if video
	} else {
		const char* filename = "/home/marcel/Obrazy/road_black.JPG";
		cout << "ok\n";
		src = imread(filename, IMREAD_COLOR);
		if (!src.data)
			cout << "reading error\n";
		target = src;
		cvtColor(src, temp, COLOR_RGB2GRAY);
		Canny(temp, temp3, 50, 200);
		namedWindow("after Canny without filter", 0);
		imshow("after Canny without filter", temp3);
		get_x_center(temp3, target, 100, blue); //niebieski

		namedWindow("after transformations", WINDOW_NORMAL);
		imshow("after transformations", target);
		waitKey(0);
		//end if photo
		return 0;
	}

}

double get_x_center(Mat &src, Mat &target, int threshold, cl color) {
	vector<Vec4i> p_lines;

	HoughLinesP(src, p_lines, 1, CV_PI / 180, threshold, 30, 10);
	double sum_left = 0, sum_right = 0;
	double num_left = 0, num_right = 0;
	size_t i;
	double longest_line = 0;
	double line_len = 0;
	double longest_line_nr;
	for (i = 0; i < p_lines.size(); i++)
	{
		Vec4i l = p_lines[i];
		line_len = sqrt(pow((l[0] - l[2]), 2) + pow((l[1] - l[3]), 2));
		if (line_len > longest_line)
		{
			longest_line = line_len;
			longest_line_nr = i;
		}
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
	if(longest_line_nr > p_lines.size())
	{
	//	cout << "nie ma takiej lini!!\nlongest_line_nr jest zbyt duze!!\n";
		return -1;
	}
	Vec4i l = p_lines[longest_line_nr];
		line(target, Point(l[0], l[1]), Point(l[2], l[3]), colors[yellow], 20,
			LINE_AA);

	return center;
}

void filtr(Mat &src, Mat &target) {
	Mat kernel = (Mat_<char>(3, 3) << 0, 0, 0, 1, 0, -1, 0, 0, 0);
	filter2D(src, target, -1, kernel);
}

