#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//영상 타입확인,
void image_type(Mat& img) { //그레일 영상 처리수행한다고 하자
	CV_Assert(img.type() == CV_8UC1); //gray scale 검사, 
	//CV_Assert()는openCV에서 제공하는 매크로함수로서 괄호가 참이면 진행, 거짓이면 에러발생
}
//같은 사이즈 가져오기
void same_size() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {	cerr << "image load failed!!" << endl; return;	}
	Mat dst(src.rows, src.cols, src.type()); //이런방법이 있을수있다
}

int main() {
	

	return 0;
}