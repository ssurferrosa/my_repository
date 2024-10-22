#include "opencv2/opencv.hpp"
#include <iostream>
#include <time.h>

using namespace std;
using namespace cv;

//각 성분은 BGR 0~255범위로 각생상성분은 uchar사용, 총3개니깐 <Vec3b> 을 사용해야 한픽셀을 표현가능(정확히 3바이트)
// 참조는 Mat::at()사용, 템플릿클래스라서 <Vec3b>표시한다
void color() {
	Mat src = imread("butterfly.jpg", IMREAD_COLOR);
	if (src.empty()) { cerr << "image load failed!!" << endl;  return; }

	Mat dst(src.rows, src.cols, src.type());
	//inverse하고싶으면 Mat dst = Scalar(255,255,255) - src; 하면된다

	//참조해보자
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			Vec3b& pixel = src.at<Vec3b>(i, j);
			//사실 pixel[0], pixel[1]이런식으로 cout하면되는데 uchar으로 선언하는거 알아가자
			uchar b = pixel[0]; uchar g = pixel[1]; uchar r = pixel[2]; //각각(i,j좌표의) B,G,R저장
			int bb = static_cast<int>(pixel[0]);
			int gg = static_cast<int>(pixel[1]);
			int rr = static_cast<int>(pixel[2]); //이게 uchar을 출력하면 이상한게나와서 확인을위해 int로바꾸자
			cout << "B: " << bb << "G: " << gg << "R: " << rr << endl;
			if (j == 2)
				break; //조금만출력하자
		}
	}
	imshow("src", src);
}
	// 컬러 추출해보자 imread로 true color가져오면 uchar사용하고 세개의 채널을 갖는 Mat객채니깐(CV_8UC3) Mat을 쪼개는 split()함수사용
	// void split(const Mat& src Mat* mvbegin)  || void split(InputArray src, OutputArray mv); src:입력다채널행렬, mvbegin 분리된1채널저장 Mat배열주소, mv:분리된 1채널 저장벡터
	//vector<Mat> 후자 사용할꺼면 으로 받자
void color_split(){

		Mat src = imread("candies.png");
		if (src.empty()) { cerr << "image load failed!!" << endl;  return; }

		vector<Mat> bgr_planes;
		split(src, bgr_planes);
		
		vector<Mat> marge = { bgr_planes[0],bgr_planes[1] };
		Mat B_and_G;
		merge(marge, B_and_G);

		imshow("src",src);
		imshow("B", bgr_planes[0]);
		imshow("G", bgr_planes[1]);
		imshow("R", bgr_planes[2]);
		//imshow("merge(B_and_G)", B_and_G);

	}
// equalizeHist()함수 사용가능. 하지만 CV_8UC1영상을 입력으로 받는 맴버함수라서 3채널을 쪼개서 간다
//이때 색감은 건들이지않고 명암비를 조절하기위해 밝기정보만 있는  YCrCb를 쓴다Y(Iuminance), Cr,Cb(chrominance색상차이)
void color_equalization() {
	Mat src = imread("candies.png",IMREAD_COLOR);
	if (src.empty()) { cerr << "image load failed!!" << endl;  return; }

	//cvtColor
	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);
	//split
	vector<Mat> ycrcb_planes;
	split(src_ycrcb, ycrcb_planes);
	//equalization(Y channel)     -> equalizeHist(InputArray src, OutputArray dst)
	equalizeHist(ycrcb_planes[0], ycrcb_planes[0]);
	//merge
	Mat dst_ycrcb;
	merge(ycrcb_planes, dst_ycrcb);
	// DeConvert
	Mat dst;
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);
	imshow("src", src);
	imshow("dst", dst);
}
// 색상 정보가 설정되어있는 HSV가 유리하다 예를들어 노란색은 H가 30근방이여서 20~40정도 쓴다
//void inragne(InputArray src, InputArray lowerb, InputArray upperb, OutPutArray dst); dst반환은 지정색포함되있으면 휜색,아니면검은색마스크 영상을 반환
//뭔가 return하는게없는데 사실 dst에서 return한다. src가 채널2개라면 &&조건으로 동작한다. src가 CV_8CU1이면 밝기로 동작한다
void color_inrange() {
	//define lowerb, upperb about HSV(Hue(색), Saturation(채도), Value(명도))
	int lower_hue = 20, upper_hue = 40; //saturation은 선명한거원하니 100~255로, 명도영향무시위해서 0~255로
	Scalar lowerb(lower_hue, 100, 0);
	Scalar upperb(upper_hue, 255, 255);

	//imread
	//Mat src = imread("candies.png", IMREAD_COLOR);   if (src.empty()) { cerr << "image load failed!!" << endl;  return; }
	
	//convert
	//Mat src_hsv;
	//cvtColor(src, src_hsv, COLOR_BGR2HSV);

	VideoCapture cap(0); // VideoCapture cpa; cap.open(0);과 동일 
	//fps setting
	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;
	//FPS(frames per second)가 30일경우 delay의 값은 33이며 이는 매 프레임을 33ms간격으로 출력함을 의미
	int delay = cvRound(1000 / fps); //이렇게 간단한 산수로 구현가능

	if (!cap.isOpened()) {
		std::cerr << "camera open failed!" << endl; 
		return;
	}
	Mat frame;

	while (true) {
		cap >> frame;
		if (frame.empty()) {
			std::cerr << "frame.empty()_issue" << endl; 
			break;
		}
		//convert hsv
		Mat frame_hsv;
		cvtColor(frame, frame_hsv, COLOR_BGR2HSV);
		Mat mask;
		inRange(frame_hsv, lowerb, upperb, mask);
		

		imshow("src(frame)", frame);
		imshow("mask", mask);

		if (waitKey(delay) == 27) // ESC 누르면 break되게 해주자 10ms를 기다린다 0넣으면 무한이 기다린다
			break;
	}


	//inrage
	//Mat mask;
	//inRange(src_hsv, lowerb, upperb, mask);

	//imshow("src", src);
	//imshow("mask", mask);


}

void detct_circle() {
	VideoCapture cap(0); // VideoCapture cpa; cap.open(0);과 동일 
	//fps setting
	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS: " << fps << endl;
	//FPS(frames per second)가 30일경우 delay의 값은 33이며 이는 매 프레임을 33ms간격으로 출력함을 의미
	int delay = cvRound(1000 / fps); //이렇게 간단한 산수로 구현가능

	if (!cap.isOpened()) {
		std::cerr << "camera open failed!" << endl;
		return;
	}
	Mat frame;

	while (true) {
		cap >> frame;
		if (frame.empty()) {
			std::cerr << "frame.empty()_issue" << endl;
			break;
		}
		Mat src;
		cvtColor(frame, src, COLOR_BGR2GRAY);
		Mat blurred;
		blur(src, blurred, Size(3, 3));   //입력 영상 src의 잡음을 제거하는 용도로 blur함수사용

		vector<Vec3f> circles;
		HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30,0,100);
		for (Vec3f c : circles) {
			Point center(cvRound(c[0]), cvRound(c[1]));
			int radius = cvRound(c[2]);
			circle(frame, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
		}
		imshow("src(frame)", frame);

		


		if (waitKey(100) == 27) // ESC 누르면 break되게 해주자 10ms를 기다린다 0넣으면 무한이 기다린다
			break;
	}



}



int main() {

	//color();
	//color_split();
	//color_equalization();
	
	color_inrange();
	//detct_circle();
	waitKey();
	destroyAllWindows();

	return 0;


}