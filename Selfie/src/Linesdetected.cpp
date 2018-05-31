/*
 * Linesdetected.cpp
 *
 *  Created on: 31 maj 2018
 *      Author: marcel
 */

#include "Linesdetected.h"
#include"Myline.h"
#include<vector>
#include<iostream>

namespace cv {
Lines_detected::Lines_detected(){
	all_lines = NULL;
	quantity = 0;
//	cout << "null Lines_detected constructor\n";

}

Lines_detected::Lines_detected(const vector<Vec4i> v) {

	quantity = v.size();
	all_lines = new Myline[quantity];

	for(unsigned i=0;  i<quantity;  i++)	//zapełniam tablice all_lines objektami Myline
	{										//w kolejnosci domyślnej( w jakiej HoughlinesP wykryl te linie )
		Myline l(v[i], i+1);
		all_lines[i] = l;
	//	cout << all_lines[i].get_ID() << "\t\t" << all_lines[i].get_x_center() << endl;
	}
	cout << "ok\n";
}

Lines_detected::~Lines_detected() {
	// TODO Auto-generated destructor stub
	delete[] all_lines;
	cout << "destructing all_lines\n";
}

void Lines_detected::display(){
//	cout << "quantity:\t" << quantity<<endl;
//	cout << "max ID: " << all_lines[quantity-1].get_ID() <<endl;
	for(unsigned i=0;  i<quantity;  i++)
	{
		cout << all_lines[i].get_ID() << "\t" << all_lines[i].get_x_center() << endl;
	}
	cout << "***********************************************************\n\n";
}

void Lines_detected::sort(){
	qsort(all_lines, quantity, sizeof(Myline), compare_points);
}

 int compare_points(const void* left, const void *right){
	 cout << "ok ";
	Myline l_line = *(Myline *)left;
	Myline r_line = *(Myline *)right;

	if(l_line.get_x_center() < r_line.get_x_center())
		return -1;
	if(l_line.get_x_center() == r_line.get_x_center())
		return 0;
	if(l_line.get_x_center() > r_line.get_x_center())
		return 1;

	/*
	  if ( *(Vec4i*)left <  *(Vec4i*)right ) return -1;
	  if ( *(Vec4i*)left == *(Vec4i*)right ) return 0;
	  if ( *(Vec4i*)left >  *(Vec4i*)right ) return 1;
	*/
	return 0;

}

} /* namespace cv */
