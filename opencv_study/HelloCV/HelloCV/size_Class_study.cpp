#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// 영상 또는 사각형의 크기를 표현 맴버변수 width, height 맴버함수 area 
int main() {
	cv::Size sz1, sz2(10, 20);
	sz1.width = 5; sz1.height = 10;
	cout << "sz1: " << sz1 << "  sz2: " << sz2 << endl;

	Size sz3 = sz1 + sz2;
	Size sz4 = sz1 * 2;

	//area() return: width * height
	int area1 = sz4.area();

	cout << "sz3: " << sz3 << "  sz4: " << sz4 << endl;
	cout << "area1 = sz4.area(): " << area1 << endl;



}
