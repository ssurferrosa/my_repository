#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//회전된 사각형을 표시 맴버변수: Point2f center(회전된 사각형의 중심좌표), Size2f size, float angle 
//Point_, Size_, Rect_클래스와 다르게 템플릿 클래스가아님 맴버 변수정의에 나와있듯이 전부 float을  사용함, 
//c++표준스트림 출력 지원X(cout사용 불가능 하다는 뜻)
//----------------------------------
// Range 클래스 : 범위를 표현할때 씀 cv::Range(0,10)하면 0~9까지 범위를 표현함 파이썬느낌나는거(간단하니깐 따로 소스코드는 안만듬)

int main() {
	//40,30좌표에 시계방향으로 30도 돌아가있는 사각형
	cv::RotatedRect rr1(Point2f(40, 30), Size2f(40, 20), 30.f);
	//bounding box(회전된 사각형을 감싸는 최소 크기의 사각형 정보
	Rect br = rr1.boundingRect();
	// 회전된 사각형 객체의 네 꼭지점
	Point2f pts[4];
	rr1.points(pts);
	cout << "pts[0]: " << pts[0] << "  pts[4]: "<<pts[4] << endl;
	

	return 0;
}