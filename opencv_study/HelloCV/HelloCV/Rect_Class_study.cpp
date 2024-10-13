#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//사각형의 위치와 크기정보를 표현 맴버변수 x,y(좌측상단점의 좌표), width,height
// 맴버함수area, empty, contains(point_형클래스 input이 사각형내부에 있는지검사)

int main() {
	Rect rc1;
	cout << "rc1 [0x0 from(0,0)]: " << rc1 << endl;
	cout << "rc1.empty: " << rc1.empty() << endl;
	

	Rect rc2(10, 10, 60, 40); //rc2.x = 10, rc2.y = 10, rc2.width = 60, rc2.height = 40
	cout << "rc2 [60x40 from(10,10)]: " << rc2 << endl;

	//Size_클래스 객채와의 산줄 연산자 재정의되어있음
	Rect rc3 = rc1 + Size(50, 40);
	cout << "rc3  = rc1 + Size(50,40) ->> [50x40 from(0,0)]: " << rc3 << endl;

	// Point_클래스 객채와의 산줄 연산자 재정의되어있음
	Rect rc4 = rc2 + Point(10, 20);
	cout << "rc4  = rc1 + Point(10,20) ->> [60x40 from(10+10,10+20)]: " << rc4 << endl;
	//&(and) |(or) 연산자도 놀랍게도 가능
	Rect rc5 = rc3 & rc4;
	cout << "rc3&rc4  : " << rc5 << endl;

	Rect rc6 = rc3 | rc4;
	cout << "rc3|rc4  : " << rc6 << endl;



	return 0;
}