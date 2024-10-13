#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	cout << "Hello OpenCV" << CV_VERSION << endl;

	cv::Mat img;
	//img = cv::imread("C:\opencvdata\lenna.bmp"); // bmp영상파일 불러와서 mat객체 변환
	img = cv::imread("lenna.bmp"); // bmp영상파일 불러와서 mat객체 변환
	if (img.empty()) {
		std::cerr << "Image load failed" << endl; //국룰
		return -1;
	}

	cv::namedWindow("my_image",WINDOW_NORMAL);
	cv::imshow("image", img);

	cv::waitKey();
	return 0;





}