#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;
//opencv 는 saturate계산이 구현되어있다(직접구현하는건 필요하면하기.일반적으로 구현된거쓰는게 최적화잘되있다)
void callback_on_brightness(int pos, void* userdata); //callback_function for Trackbar

void brightness1() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "image load failed!" << endl; return; }
	// (연산자방법)=(add,subtract) ||| 직접구현하려면saturate_cast()함수사용
	Mat dst1 = src.clone();  dst1 += 100; //+=, -= operator overloading is provided
	Mat dst2 = src.clone(); dst2 -= 50;
	
	imshow("dst1", dst1);  imshow("dst2", dst2); waitKey(); destroyAllWindows();
}
//int createTrackbar(1: const String& trackbarname, 2: const String& winname, 3: int*value,
//					4: int count, 5: TrackbarCallback onChange = 0, 6: void*userdata = 0)
// 1트랙바이름,트랙바 2생성창이름, 3트랙바위치받을 정수형변수주소, 4트랙바최대위치,
// 5트랙바위치변경시 callback함수이름(함수의포인터) null이면 콜백호출x value로 지정한변수값만갱신,
// 6콜백에 전달할 사용자 데이터의 포인터 ||||| 반환값 정상동작시 1 실패시 0

void brightness2() { //트랙바 방법 해보자
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "image load failed!" << endl; return; }
	namedWindow("dst_withTrackbar"); //createTrackbar에서 winname과 이름같아야함

	createTrackbar("Brightness_withTrackbar", //입력영상src의 주소를 트랙바 콜백함수의 사용자데이터로 설정
		"dst_withTrackbar", 0, 100,callback_on_brightness, (void*)&src); //콜백쓸때 (void*)로 캐스팅하고 주는게 국룰
	callback_on_brightness(0, (void*)&src);//실행시 dst창에 레나영상이 표시되도록 강제로 콜백호출(원래 콜백은 이렇게쓰는건 이상하긴한데 이거없으면 트랙바 움직이고나서 레나영상나옴 편법이라고 생각하자)

	waitKey(); destroyAllWindows();

}
void callback_on_brightness(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;
	imshow("dst", dst);
}
//contrast는 *연산자로 구현가능하다
void contrast() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "image load failed!" << endl; return; }
	//기본적인 contrast조작법
	float s = 2.f;
	Mat dst1 = s * src; 
	//효율적인 조절법
	float alpha = 1.f; //이건 경험에의해 조절 -1이상이면됨
	Mat dst2 = src + (src - 128) * alpha;
	imshow("dst1", dst1);  imshow("dst2", dst2); waitKey(); destroyAllWindows();

}


int main() {
	//brightness1();
	//brightness2();
	contrast();
	return 0;
}