#include"imgproc.hpp"
#include"core.hpp"
#include"highgui.hpp"
#include"videoio.hpp"
#include<iostream>
#include<cmath>
#include<string>
#include "this_n_that.hpp"
#include"Linesdetected.h"

const string trackbar_win = "trackbars_windows";
int Hough_threshold;
int sigma_x;
int sigma_y;
Mat dest, source_for_Hough;


extern const Vec4i colors[7] = {
		Scalar(255,0,0), Scalar(0,0,255), Scalar(0,255,0),
		Scalar(0,255,255), Scalar(255,0,210), Scalar(255,255,255), Scalar(0,0,0)
};

/**
 * @function main
 */
int main(int argc, char** argv) {
	Mat src;
	Mat temp, temp2, temp3, target;

	if (argc == 2)
	{
		if (strcmp(argv[1], "video") == 0) {

			VideoCapture cap(1);
			if (!cap.isOpened()) {
				cout << "nie mozna odczytac z kamery\n";
				return -1;
			}

			namedWindow(trackbar_win, 0);
			trackbars();

			/*
			 * t = 1000*((double)getTickCount() - t)/getTickFrequency();
			 */
			double t = 0;
			for (;;) {
				t = (double) getTickCount();
				for (unsigned i = 0; i < 100; i++) {

					cap >> src;
					//GaussianBlur(src, src, Size(2, 2), sigma_x, sigma_y);
					filtr(src, src);
					target = src;
					cvtColor(src, temp, COLOR_RGB2GRAY);
					Canny(temp, temp3, 50, 200);
					namedWindow("after Canny without filter", 0);
					imshow("after Canny without filter", temp3);
					get_x_center(temp3, target, Hough_threshold, blue);
					namedWindow("after transformations", WINDOW_NORMAL);
					imshow("after transformations", target);
					if (waitKey(30) >= 0)
						return 0;
				}
				t = (((double) getTickCount() - t) / getTickFrequency()) / 100;	//duration of 100 frames
				cout << "\t\tfps: " << 1 / t << endl;
			}
			return 0;
			//end if video
		} else if (strcmp(argv[1], "photo") == 0)
		{
			const char* filename = "/home/marcel/Obrazy/road_black.JPG";
			cout << "ok\n";
			src = imread(filename, IMREAD_COLOR);
			if (!src.data)
				cout << "reading error\n";
			namedWindow(trackbar_win, 0);
			dest = src;
			cvtColor(src, temp, COLOR_RGB2GRAY);
			filtr(temp, temp);
			Canny(temp, temp3, 50, 200);
			source_for_Hough = temp3;
			namedWindow("after Hough", 0);
			namedWindow("after Canny with filter", 0);
			imshow("after Canny with filter", temp3);
			get_x_center(temp3, dest, Hough_threshold, blue); //niebieski

			namedWindow("after transformations", WINDOW_NORMAL);
			imshow("after transformations", dest);
			waitKey(0);
			//end if photo
			return 0;
		} else if (strcmp(argv[1], "test") == 0) {

			vector<Vec4i>lines;
			const char* filename = "/home/marcel/Obrazy/road_black.JPG";
			cout << "\t\t***test mode***\n";
			src = imread(filename, IMREAD_COLOR);
			filtr(src, src);
			cvtColor(src, temp, COLOR_RGB2GRAY);
			Canny(temp, temp3, 50, 200);
			get_x_center(temp3, dest, Hough_threshold, red, &lines);
			cout << lines.size() << endl;
			Lines_detected l_det(lines);
			double t = getTickCount();
				//l_det.display();
			l_det.sort();
				//l_det.display();
			t = (((double) getTickCount() - t) / getTickFrequency());
			cout << t << endl;


			return 0;
		}
	}else	//argc !=2
	{


	}
}


void trackbars()
{
	createTrackbar("Hough_threshold", trackbar_win, &Hough_threshold, 255);
	createTrackbar("sigma_x", trackbar_win, &sigma_x, 10);
	createTrackbar("sigma_y", trackbar_win, &sigma_y, 10);

}

//int createTrackbar(const string& trackbarname, const string& winname, int* value, int count, TrackbarCallback onChange=0, void* userdata=0)

