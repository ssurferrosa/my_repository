#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//객체로부터 다양한 정보 참조해보자
int main() {
	Mat img1 = imread("lenna.bmp");
	cout << "Width: " << img1.cols << endl;;
	cout << "Height: " << img1.rows << endl;
	cout << "type : " << img1.type() << endl; //int로 반환해서 알아먹기힘드니..  if문으로 가자
	if (img1.type() == CV_8UC1)
		cout << "img1 is a grayscale image" << endl;
	else if (img1.type() == CV_8UC3)
		cout << "img1 is a truecolor image" << endl;
	else
		cout << "neither CV_8UC1 nor CV_8UC3" << endl;

	cout << "channels : " << img1.channels() << endl;

	cout << "size Mat::size() const " << img1.size() << endl;

	//행렬 원소값을 직접확인하고싶을때 만약 Mat클래스에 영상저장되있으면 imshow()로 화면 표기가능한데 행렬있으면 적절하지않음
	// <<연산자 재정의를 재공함  static inline
	//						 std::ostream& operator <<(std::ostream&out, const Mat& mtx)
	// 실제사용법은 생각보다 간단 <<왼쪽에는 std::cout적고 <<오른쪽에는 Mat객체 변수 적기
	float data[] = { 2.f,1.414f,3.f,1.732f };
	Mat mat1(2, 2, CV_32FC1, data);
	std::cout << mat1 << std::endl;





}