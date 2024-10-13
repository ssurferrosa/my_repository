#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	cv::Point pt1;
	pt1.x = 1; pt1.y = 2;

	Point pt2 = pt1 * 3;

	Point pt3 = pt1 + pt2;

	Point pt4(10, 15);

	int d1 = pt1.dot(pt2); //두점의 내적을 계산 x좌표끼리더한값+y좌표끼리 더한값 1*3 + 2*6 = 15

	bool b1 = (pt1 == pt2);

	cout << "pt1: " << pt1 << "pt2: " << pt2
		<< "pt3: " << pt3 << "pt4: " << pt4 << endl;

	cout << "int d1 = pt1.dot(pt2)'s result: " << d1 << "bool b1 = (pt1 == pt2) 's result: " << b1 << endl;

	return 0;
}