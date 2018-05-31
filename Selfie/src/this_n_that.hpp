/*
 * header_makros.hpp
 *
 *  Created on: 31 maj 2018
 *      Author: marcel
 */

#ifndef THIS_N_THAT_HPP_
#define THIS_N_THAT_HPP_
#include"imgproc.hpp"
#include"core.hpp"
#include"highgui.hpp"
#include"videoio.hpp"
#include "core/types_c.h"
#include<vector>


using namespace std;
using namespace cv;

enum cl{
	blue=0, red, green, yellow, purple, white, black
};

#define CHECK(x) if(!x.data){	std::cout << "nie ma nic w srodku!!\n"; return -1;}else std::cout<<"ok\n";

using namespace std;
using namespace cv;

/// Function Headers

void trackbars();
void filtr(Mat&, Mat&);
double get_x_center(Mat &src, Mat &img, int, cl);
double get_x_center(Mat &src, Mat &img, int, cl, vector<Vec4i>*);
int compare_points(const void *, const void *);





#endif /* THIS_N_THAT_HPP_ */
