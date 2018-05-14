/*
 * main.cpp
 *
 *  Created on: 14 maj 2018
 *      Author: marcel
 */


#include"imgproc.hpp"
#include"core.hpp"
#include"highgui.hpp"
#include<iostream>

using namespace std;
using namespace cv;

/// Global variables

/** General variables */
Mat src, edges;
Mat src_gray;
Mat standard_hough, probabilistic_hough;
int min_threshold = 50;
int max_trackbar = 150;

const char* standard_name = "Standard Hough Lines Demo";
const char* probabilistic_name = "Probabilistic Hough Lines Demo";

int s_trackbar = max_trackbar;
int p_trackbar = max_trackbar;

/// Function Headers
void help();
void Probabilistic_Hough(int, void*);

/**
 * @function main
 */
int main(int argc, char** argv) {

	// Read the image
	String imageName("/home/marcel/Obrazy/road.JPG"); // by default
	if (argc > 1) {
		imageName = argv[1];
	}
	src = imread(imageName, IMREAD_COLOR);

	if (src.empty()) {
		help();
		return -1;
	}
	/// Pass the image to gray
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	/// Apply Canny edge detector
	Canny(src_gray, edges, 50, 200, 3);

	/// Create Trackbars for Thresholds
	char thresh_label[50];
	sprintf(thresh_label, "Thres: %d + input", min_threshold);

	namedWindow(probabilistic_name, 0);
	createTrackbar(thresh_label, probabilistic_name, &p_trackbar, max_trackbar,
			Probabilistic_Hough);

	/// Initialize
	Probabilistic_Hough(0, 0);
	waitKey(0);
	return 0;
}

/**
 * @function help
 * @brief Indications of how to run this program and why is it for
 */
void help() {
	printf("\t Hough Transform to detect lines \n ");
	printf("\t---------------------------------\n ");
	printf(" Usage: ./HoughLines_Demo <image_name> \n");
}

/**
 * @function Probabilistic_Hough
 */
void Probabilistic_Hough(int, void*) {

	vector<Vec4i> p_lines;
	cvtColor(edges, probabilistic_hough, COLOR_GRAY2BGR);

	HoughLinesP(edges, p_lines, 1, CV_PI / 180, min_threshold + p_trackbar, 30,
			10);

	/// Show the result
	double width = probabilistic_hough.rows;
	cout << "szerokosc (piksele): "<< width << endl;
	size_t i = 0;
	for (i = 0; i < p_lines.size(); i++) {
		Vec4i l = p_lines[i];
		line(probabilistic_hough, Point(l[0], l[1]), Point(l[2], l[3]),
				Scalar(255, 0, 0), 3, LINE_AA);
		//  sum_ex+=l[0];
	}

	imshow(probabilistic_name, probabilistic_hough);
}



