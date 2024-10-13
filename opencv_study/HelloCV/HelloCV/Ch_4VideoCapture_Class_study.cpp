#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;
//주의!! opencv의 그리기함수는 영상의 픽셀값을 변경시키니깐 원본은 Mat::clone(), Mat::copyTo()해주자
//대부분의 동영상파일은 코덱(codec)을 이용해 압축된형태로 저장. 
// opencv는 현재 널리사용되는 MPEG-4, H.264등을 제공해서 쉽게불러와서 쉽게 사용가능
//VideoCapture 클래스 선언, open맴버함수로 영상을 여는 구조 get, set으로 properties를 확인,접근한다
int video_in_me() {
	VideoCapture cap(0); // VideoCapture cpa; cap.open(0);과 동일 0은 컴퓨터에게 알아서 카메라 맞기는거

	if (!cap.isOpened()) {
		std::cerr << "camera open failed!" << endl; //국룰 연결잘안되있거나 다른프로그램이 카메라쓰면 에러
		return 0;
	}
	//여러가지 VideoCaptureProperties들이 있다 get이라는 맴버 함수를 이용한다
	//get은 double return하는데 실제 코드에서 프레임크기 저장위해 cvRound(opencv에서 제공하는 반올림) 쓰자
	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	
	//카메라 장치로부터 프레임(한장의 정지영상)을 받아보자
	Mat frame;
	while (true) {
		//cap.read(frame)해도된다 완전히 같은기능을하고 
		//VideoCapture에는 >>가 재정의 되어있는데 >>가 편하니깐 주로 이거쓴다
		cap >> frame;
		if (frame.empty()) {
			std::cerr << "frame.empty()_issue" << endl; //국룰
			break;
		}

		Mat inversed = ~frame;
		imshow("frame", frame);
		imshow("inversed", inversed);
		
		if (waitKey(10) == 27) // ESC 누르면 break되게 해주자 10ms를 기다린다 0넣으면 무한이 기다린다
			//참고로 waitKey는 아스키코드로 사용자가 누른키를 반환해준다
			break;
	}

	destroyAllWindows();


	return 0;
}

int video_in_stopwatch() {
	VideoCapture cap("stopwatch.avi"); // VideoCapture cpa; cap.open("stopwatch.avi")과 동일

	if (!cap.isOpened()) {
		std::cerr << "camera open failed!" << endl; //국룰 연결잘안되있거나 다른프로그램이 카메라쓰면 에러
		return 0;
	}
	//여러가지 VideoCaptureProperties들이 있다 get이라는 맴버 함수를 이용한다
	//get은 double return하는데 실제 코드에서 프레임크기 저장위해 cvRound(opencv에서 제공하는 반올림) 쓰자
	cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;
	//딜레이를 설정하고 waitKey에 넣어보자
	
	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;
	//FPS(frames per second)가 30일경우 delay의 값은 33이며 이는 매 프레임을 33ms간격으로 출력함을 의미
	int delay = cvRound(1000 / fps); //이렇게 간단한 산수로 구현가능

	//카메라 장치로부터 프레임(한장의 정지영상)을 받아보자
	Mat frame;
	while (true) {
		//cap.read(frame)해도된다 완전히 같은기능을하고 
		//VideoCapture에는 >>가 재정의 되어있는데 >>가 편하니깐 주로 이거쓴다
		cap >> frame;
		if (frame.empty()) {
			std::cerr << "frame.empty()_issue" << endl; //국룰
			break;
		}

		Mat inversed = ~frame;
		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27) // ESC 누르면 break되게 해주자 10ms를 기다린다 0넣으면 무한이 기다린다
			break;
	}

	destroyAllWindows();


	return 0;
}

void camera_in_video_out() {
	//이건 나중에
}

int main() {
	//video_in_me();
	video_in_stopwatch();
	return 0;
}