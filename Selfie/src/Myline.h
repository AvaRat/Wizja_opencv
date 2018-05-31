/*
 * Myline.h
 *
 *  Created on: 31 maj 2018
 *      Author: marcel
 */
#include"imgproc.hpp"
#include"core.hpp"
#include"highgui.hpp"
#include"videoio.hpp"
#include<iostream>
#include<cmath>
#include<string>
	//#include "Linesdetected.h"


#ifndef MYLINE_H_
#define MYLINE_H_

namespace cv{

class Myline{
public:
	Myline();
	Myline(const Vec4i, int Id);
	virtual ~Myline();
	int get_x_center();
	int get_ID();
private:
	int x1;
	int y1;
	int x2;
	int y2;
	int x_center;
	int y_center;
	int lenght;
	int ID;
};

}
#endif /* MYLINE_H_ */
