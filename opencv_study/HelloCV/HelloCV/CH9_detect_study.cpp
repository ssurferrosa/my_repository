#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;
// canny edge detection로 엣지를 검출한다(가장많이사용되는) -> hough circle transform, hough line transform 으로 라인,원검출가능
// 미분영상있으면 다른입력방식사용(찾아보기)
// void Canny(1: InputArray image, 2: OutputArray edges, 3:double threshold1, 4:double threshold2,
//			  5: int apertureSize = 3, 6: bool L2gradient = false)  1,2서로크기같은 8비트입력,출력영상 
// 3,4: 낮은임계,높은임계 1:2,1:3 국룰비율  5:그래디언트 계산위한 소벨 마스크 크기 6:그래디언트 크기 게산시 디폴트는 L1노름사용(계산량)  
        
Mat canny_edge_detector(const string& filename) {
	Mat src = imread(filename, IMREAD_GRAYSCALE);

	if (src.empty()) {	cerr << "Image load failed!!" << endl; return Mat() ;	}//빈 mat반환

	Mat edge;
	Canny(src, edge, 50, 100); //often using the ratio values of 1:2, 1:3

	return edge;
}
//probabilistic hough transform:  
// Void HoughLinesP(1: InputArray image, 2: OutputArray lines, 3:double rho, 4:double theta, 5: int threshold, 
// 6: double minLineLEnght = 0, 7: double MaxLineGAp = 0)
// 1: 8비트단일채널입력영상(주로 에지영상) 2: 선분시작점과 끝점 정보를 저장할 출력벡터(x1,y1,x2,y2) vector<veci> 형태국룰
// 3,4 해상도각각 픽셀단위 라디안단위(1이면 1픽셀단위, cu_pi/180이면 1degree단위)  5: 축적배열에서 직선판단 임계값 
// 6:검출 선분최소길이 7:직선간주 최대에지점간격
void hough_lines_segments(const Mat& edge_img) {
	CV_Assert(edge_img.type() == CV_8UC1); 

	vector<Vec4i> lines;
	HoughLinesP(edge_img, lines, 1, CV_PI / 180, 160, 50, 5); //1픽셀,1도단위,160threshold, 50을 최소검출길이로, 5를 직선 최대에지점간격으로

	//cvtColor 써서 엣지영상을 3채널 컬러 영상으로 변환해 dst에 저장
	Mat dst;
	cvtColor(edge_img, dst, COLOR_GRAY2BGR);
	// 범위기반 for문 즐겨써보자
	for (Vec4i l : lines) {
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255),
			2, LINE_AA);
	}
	// line에 [147, 323, 404, 214] 이렇게 저장된다. hough 부호 변환?값? 신경안써도 ok
	
	imshow("dst",dst);
	
}
// void HoughtCircles(1: InputArray image,2: OutputArray circles, 3:int method, 4:double dp,
// 5: double minDist, 6: double param1 = 100, 7: double param2 = 100, 8: int minRadius = 0, 9: int maxRadius = 0;)
// 1: 그레이스킬원본영상(에지아님), 2 검출된 원정보 저장 출력벡터(Vector<Vec3f또는Vec4f>국룰,
// 3: HOUGH_GRADIENT만 지정가능, 4:입력영상과 축적배열 크기비율
// 5: 인접한 원중심의 최소거리, 6:CANNY에지 검출기의 높은임게값, 7: 축적배열에서 원검출위한 임계값, 8,9: 검출할 원의 최소,최대반지름
// 주의: 내부에서 sobel()함수와 canny()이용해서 그래디언트와 엣지영상 계산후 원을검출하는구조라서 원본넣는다
// 낮은임계값은 입력하는게 따로없는데 param2의 절반값을 내부적으로 사용한다, 검출할 원의 대략적인 크기알고있으면 8,9적절하게 지정해서 연산속도 상향가능
void hough_circles(const string &filename) {
	Mat src = imread(filename, IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!!" << endl; return; }


	Mat blurred; 
	blur(src, blurred, Size(3, 3));   //입력 영상 src의 잡음을 제거하는 용도로 blur함수사용

	vector<Vec3f> circles;
	HoughCircles(blurred, circles, HOUGH_GRADIENT, 1, 50, 150, 30);

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (Vec3f c : circles) {
		Point center(cvRound(c[0]), cvRound(c[1]) );
		int radius = cvRound(c[2]);
		circle(dst, center, radius, Scalar(0, 0, 255), 2, LINE_AA);
	}

	imshow("src", src);
	imshow("dst", dst);
	

}

int main() {
	string filename1 = "building.jpg";
	string filename2 = "coins.png";

	Mat img1 = canny_edge_detector(filename1);
    //Mat img1 = canny_edge_detector("building.jpg");

	imshow("img1", img1);
	hough_lines_segments(img1);

	hough_circles(filename2);

	waitKey();
	destroyAllWindows();

	return 0;
}