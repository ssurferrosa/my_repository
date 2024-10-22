#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;
//createing Histogram array -> drawing Histogram(describe by line)
//void calcHist(1:const Mat*images ,2:int nimage, 3:const int*,4: InputArray mask,
//				(5:OutputArray hist, 6: int dims, 7:const int* histSize 8: const float** ranges,
//	(9: bool uniform = ture, 10: accumulate = false)  9,10은 dafault쓰면 등간격하고,초기화한후 행렬만듬(그대로쓰기)
// 2는 입력영상갯수, 3은 히스토그램을 구할 채널을 나타내는 정수형배열, 4는 전부하고싶으면 noArray()5는 출력히스토그램(CV_32F사용),
// 6은 출력히스토그램 차원수, 7은 각차원의 히스토그램 배열크기(즉, 각차원의히스토그램 빈갯수)
// 8은 각차원의 히스토그램범위(여기선 9,10 디폴트로할꺼니 range[i]는 각차원의 최소값과 최대값으로 구성된배열	
Mat calGrayHist(const Mat& img) {
	CV_Assert(img.type() == CV_8UC1);
	//256개의 빈을 가지게 해보자
	Mat hist;
	int number_of_image = 1;
	int channels[] = { 0 };
	int dims = 1;
	const int hit_size[] = { 256 };
	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel }; //min:0, max:256

	calcHist(&img, number_of_image, channels, noArray(), hist, dims, hit_size, ranges);

	return hist;

}
//line()과 minMaxLoc()을 이용해서 구현가능 
// void minMaxLoc(1: InputArray src, 2:double* minVal, 3: double* maxVal = 0, 4:Point* minLoc = 0,
// 5: Point* maxLoc = 0, 6: InputArray mask = noArray() ) 
// 2,3은 최소,최대값받을 double변수주소(필요없으면0지정) 4,5는 최소,최대위치받을 point변수주소(필요없으면0지정)
// 6은 마스크 영상의 픽셀값이 0이아닌 위치에서만 연산수행 122p참고
Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;//address for maxvalue
	minMaxLoc(hist, 0, &histMax);
	//256개의 빈을 갖는 hist행렬로부터 가로가 256픽셀, 세로가 100픽셀인 크기의 히스토그램 생성
	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)),
			Scalar(0));
	}
	return imgHist;

}
int main() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "image load failed!" << endl; return 0; }
	Mat hist = calGrayHist(src);
	Mat hist_img = getGrayHistImage(hist);

	imshow("src", src);
	imshow("srchist", hist_img);

	waitKey(); destroyAllWindows();


	return 0;
}