#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;
// Mat 정의, 복사, Region_of_interest, 필요한부분추출, 원소값접근(Mat::at, Mat::ptr)

int main() {
	//---------------------------------Defination of Mat --------------------
	Mat img1;
	cout << "img1.empty() : " << img1.empty() << endl;

	//Method1:  Mat::Mat(int rows, int cols, int type)
	Mat img2(480, 640, CV_8UC1); //unsinged char, 1-channel
	Mat img3(480, 640, CV_8UC3); //unsinged char, 3-channel
	         //Size(480,60)이렇게 사이즈 클래스도 가능
			
	//Method2: Mat::Mat(Size size, int type, const Scalar& s) 스칼라 클래스로 초기화까지 하기(보통이걸사용) 
	Mat img4(480, 640, CV_8UC1, Scalar(128)); //(grayscale image)
	Mat img5(480, 640, CV_8UC1, Scalar(0, 0, 128)); // B G R순서로 입력 빨강으로 초기화(ture colcor)
	
	//Method3: 초기화를 0,1,단위행렬로하는경우가 많아 따로 정의가되어있음
	// static MatExpr Mat::zeros(int rows, int cols, int type)
	Mat mat1 = Mat::zeros(3, 3, CV_32SC1); // int, 1-channel
	Mat mat2 = Mat::ones(3, 3, CV_32FC1); // float, 1-channel
	Mat mat3 = Mat::eye(3, 3, CV_32FC1); // float, 1-channel 단위행렬 1 0 0;0 1 0; 0 0 1

	//Method4: 외부 메모리 공간의 주소를 지정(서로 메모리공간 공유)
	// Mat::Mat(int rows, int cols, int type, void* data, size_t = step=AUTO_SETP) 맨마지막인수는 일단 신경x
	float data[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat4(2, 3, CV_32FC1, data); //원소갯수랑 자료형같아야함 1 2 3; 4 5 6됨 

	//Method5: Mat_클래스 이용(Mat_는 Mat 클래스를 상속하여만든 템플릿 클래스(Mat랑Mat_랑 서로 상호변환가능)
	// <<연산자와 m를 이용함 (서로 메모리공유)
	Mat_<float> mat5_(2, 3);
	mat5_ << 1, 2, 3, 4, 5, 6;
	Mat mat5 = mat5_;
	//한방에 하고싶으면 Mat mat5 = (Mat_<float>(2,3) << 1,2,3,4,5,6);
	//또한 open4.0에서는 C+11의 초기화 리스트를 이용한 행렬 초기화 지원해서 
	// Mat mat5 = (Mat_<float>(2,3), {1,2,3,4,5,6}); 이것도 가능

	//Method6: 이미 생성된 객체에 새로운 행렬을 할당하려면 create쓴다(새로만든게 크기다르면 기존메모리해체 새로만듬)
	// 하지만 create는 초기화 기능이없어서 mat = 연산사 재정의(Sclar같은거) || Mat::seTo() 를 사용한다
	//Mat& Mat::operator = (const Scalar& s) 이고 Mat& Mat::setTo(InputArray value, InputArray mask = noArray())이다
	mat4.create(256, 256, CV_8UC3); //uchar, 3-channels
	mat4 = Scalar(255, 0, 0); //파란색으로 초기화
	mat5.create(4, 4, CV_32FC1); //float, 1-channel
	mat5.setTo(1.f); //모든 원소값을 1.f로 초기화 mat5.setTo(Scalar(1.f))하는게 좋은것같긴하다
	cout << mat5 << endl;

	//--------------------copy, roi(Region of Interest) --------------------
	Mat original = imread("cat.bmp");
	
	
	// shallow copy(share each others data)
	Mat copy1 = original; //이런식으로 복사생성자도 지원하고 Mat copy1; copy1 = original;같이 대입연산자도 지원
	
	//deep copy(Assign new memory and copy it) Mat::colone() 혹은 Mat::copyTo() 맴버함수를 이용한다
	Mat copy2 = original.clone();
	Mat copy3;
	original.copyTo(copy3);

	

	//관심있는부분만 추출해보고 그걸 반전시켜보자(shallow copy이다) deepcopy하려면 copy3(Rect(220, 120, 340, 240));.clone한다
	Mat region_of_interest = copy3(Rect(220, 120, 340, 240));
	region_of_interest = ~region_of_interest;

	copy1.setTo(Scalar(0, 255, 255)); //copy1은 shallow copy라서 원본도 바뀐다
	
	imshow("original", original); 
	imshow("shallow copy", copy1); 
	imshow("deep copy", copy2);
	imshow("copy3(chained by ROI)", copy3);
	imshow("region_of_interest", region_of_interest);

	
	//---------------------행,렬 추출 기본적으로 얕은복사, 깊은복사는.clone()쓰기
	// Mat Mat::rowRange(int startrow, int endrow) const;  colRange도 동일
	// Mat Mat::rowRange(const Range& r) const;
	//1행, 1열 행렬 뽑아오고싶을땐 Mat Mat::row(int y)const; Mat Mat::col(int x)const;

	//-------------------원소값 접근------------------
	//#1 template<typename _TP> _TP& Mat::at(int y, int x) 
	// 템플렛이다 보니 내가타입을 지정한다 ex) CV_8UC1이면 float지정하고 CV_8UC3이면 vec3b타입 지정한다
	Mat approch_element_for_at = Mat::ones(3, 4, CV_8UC1); //grey scale
	Mat approch_element_for_ptr = approch_element_for_at.clone();
	Mat approch_element_for_iterator = approch_element_for_at.clone();


	for (int i = 0; i < approch_element_for_at.rows; i++) {
		for (int j = 0; j < approch_element_for_at.cols; j++) {
			approch_element_for_at.at<uchar>(i, j)++;
		}
	}
	cout << approch_element_for_at << endl;
	//#2 Mat::ptr() 사용하는것(이게 빠름) 여러가지 재정의있는데 제일많이쓰는건 template<typename _TP> _Tp* Mat::ptr(int y)
	// 반환값이 _Tp*(_Tp* 타입으로 형 변환된 y번째 행의 시작주소)이다. 즉 포인터를 이용하여 접근하는것
	// 행단위로 행렬 연산참조하거나 모든원소 참조할떄는 이게좋고 임의의 좌표콕찍어서 참조할때는 Mat::at쓰는게 편함
	for (int i = 0; i < approch_element_for_ptr.rows; i++) {
		uchar* p = approch_element_for_ptr.ptr<uchar>(i);

		for (int j = 0; j < approch_element_for_ptr.cols; j++) {
			p[j]++; //approch_element.ptr<uchar>(i) 이게 i번째 행원소 시작주소를 반환하니깐 p라는 표인터 변수를 선언해서 사용
		}
	}
	cout << approch_element_for_ptr << endl;

	//#3 반복자 사용 Mat::at, Mat::ptr은 다좋은데 인자에 크기 잘못드가면 에러남 따라서 iterator(반복자 지원함)
	//MatIterator_이라는 반복자가 있음 템플릿으로 정의된클래스

	for (MatIterator_<uchar> it = approch_element_for_iterator.begin<uchar>(); it != approch_element_for_iterator.end<uchar>(); it++) {
		(*it)++;
	}
	cout <<"iterator: \n" << approch_element_for_iterator << endl;

	 

	waitKey();
	destroyAllWindows();

	return 0;
}
