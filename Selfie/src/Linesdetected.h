/*
 * Linesdetected.h
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
#include "this_n_that.hpp"
#include"Myline.h"


#ifndef LINESDETECTED_H_
#define LINESDETECTED_H_

namespace cv {


class Lines_detected {
public:
	Lines_detected();
	Lines_detected(const vector<Vec4i>);
	virtual ~Lines_detected();

	void sort();

	void display();

private:
	unsigned quantity;
	Myline *all_lines;

};

int compare_points(const void*, const void*);


} /* namespace cv */

#endif /* LINESDETECTED_H_ */
