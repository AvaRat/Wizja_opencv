#include"imgproc.hpp"
#include"core.hpp"
#include"highgui.hpp"
#include"videoio.hpp"
#include<iostream>

#define CHECK(x) if(!x.data){	std::cout << "nie ma nic w srodku!!\n"; return -1;}else std::cout<<"ok\n";

using namespace std;
using namespace cv;

/// Function Headers
void filtr(Mat&, Mat&);
double get_x_center(Mat &src, Mat &img, int, int);

/**
 * @function main
 */
int main(int argc, char** argv) {

	VideoCapture cap(1);
	if(!cap.isOpened())
	{
		cout << "nie mozna odczytac z kamery\n";
		return -1;
	}

	int center_with_filter;
//	int center_without_filter;
/*	const char* filename;
	if(argc ==2)
		filename = argv[1];
	else
		filename = "/home/marcel/Obrazy/road_black.JPG";
*/
	Mat src;
	Mat temp, temp2, temp3, target;
	for(;;)
	{
		cap >> src;
		target = src;
		cvtColor(src, temp, COLOR_RGB2GRAY);
	//	Canny(temp, temp3, 50, 200);
	//	namedWindow("after Canny without filter", 0);
	//	imshow("after Canny without filter", temp3);
	//	center_without_filter = get_x_center(temp3, target, 100, 0); //niebieski
		filtr(temp, temp2);
		Canny(temp2, temp, 50, 200);
		namedWindow("after Canny with filter", 0);
		imshow("after Canny with filter", temp);
		get_x_center(temp, target, 100, 255); //fioletowy
		namedWindow("after transformations", WINDOW_NORMAL);
		imshow("after transformations", target);

		if(waitKey(30) >= 0) break;
	}
	return 0;
}

double get_x_center(Mat &src, Mat &target, int threshold, int color) {
	vector<Vec4i> p_lines;

	HoughLinesP(src, p_lines, 1, CV_PI / 180, threshold, 30, 10);
	double sum_left = 0, sum_right = 0;
	double num_left = 0, num_right = 0;
	size_t i;
	for (i = 0; i < p_lines.size(); i++) {
		Vec4i l = p_lines[i];
		line(target, Point(l[0], l[1]), Point(l[2], l[3]),
				Scalar(255, 0, color), 3, LINE_AA);
		double x = (l[0] + l[2]) / 2;
		if (x < src.cols / 2) {
			sum_left += x;
			num_left++;
		} else {
			sum_right += x;
			num_right++;
		}
	}
	double avg_x_left = sum_left / num_left;
	double avg_x_right = sum_right / num_right;
	double center = (avg_x_left + avg_x_right) / 2;
	line(target, Point(center, target.rows), Point(center, 0),
			Scalar(255, 0, color), 3, LINE_AA);

	return center;
}

void filtr(Mat &src, Mat &target) {
	Mat kernel = (Mat_<char>(3, 3) << 0, 0, 0, 1, 0, -1, 0, 0, 0);
	filter2D(src, target, -1, kernel);
}

