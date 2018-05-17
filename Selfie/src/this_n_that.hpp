/*
 * this_n_that.cpp
 *
 *  Created on: 17 maj 2018
 *      Author: marcel
 */
#include"imgproc.hpp"
#include"core.hpp"
#include"highgui.hpp"
#include"videoio.hpp"
#include "core/types_c.h"
#include<vector>

using namespace cv;
enum cl{
	blue=0, red, green, yellow, purple, white, black
};
Vec4i colors[7] = {
		Scalar(255,0,0), Scalar(0,0,255), Scalar(0,255,0),
		Scalar(0,255,255), Scalar(255,0,210), Scalar(255,255,255), Scalar(0,0,0)
};






