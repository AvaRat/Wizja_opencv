/*
 * Myline.cpp
 *
 *  Created on: 31 maj 2018
 *      Author: marcel
 */
#include<cmath>
#include "Myline.h"

namespace cv{

Myline::Myline(){
	x1=x2=y1=y2=x_center=y_center=lenght=ID =0;
//	std::cout << "null Myline constructor\n";

}
Myline::Myline(const Vec4i l, int Id) {
	x1 = l[0];
	y1 = l[1];
	x2 = l[2];
	y2 = l[3];
	x_center = abs(l[0] - l[2]);
	y_center = abs(l[1] - l[3]);
	lenght = sqrt(pow((l[0]-l[2]), 2) + pow((l[1] - l[3]), 2));
	ID = Id;

}
int Myline::get_x_center(){
	return x_center;
}
int Myline::get_ID(){
	return ID;
}

Myline::~Myline() {
	// TODO Auto-generated destructor stub
}
}
