#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//operator, Mat::convertTo() => resize
int main() {
	float data[] = { 1.f,2.f,3.f,4.f };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1: \n" << mat1 << endl;

	//MatExpr Mat::inv(int method=DECOMP_LU)const; fullrank가아닐경우 가우스 소거법을 이용하는 DECOMP_LU가 기본값이고 
	// DECOMP_SVD(singular value decomposition 특이값분해)이걸로 pseudo_inverse matrix구할수있음) 
	//DECOMP_EIG(고윳값분해), DECOMP_CHOLESKY(Cholesky분해)도 지원
	cout << "mat1.inv() : \n" << mat1.inv() << endl;

	//transpose도 지원 
	cout << "mat1.t() \n" << mat1.t() << endl;

	//곱셈지원 MatExpr Mat::mul(INputArray m, double scale=1) const; 여기서2번째 인자는 추가적으로 곱할값 행렬표현식을 반환
	// scalar 곱한거랑 mat곱한거랑 알아서 구분해줌 -mat1하면 -1*mat한것처럼 되고..
	cout << "2*mat1 * mat1+2 \n" << (2*mat1) * (mat1 + 2) << endl;

	// 크기 재정의
	//Mat Mat::reshape(intcn, int rows=0) const; cn: 새로운 채널수(0이면 변경x), rows: 새로운행의수(0이면 변경x)
	//reshpae가 많은 재정의 있는데 제일많이쓴느게 이거고 하나의 행렬 원소 데이터를 참조하는 행렬을 반환함(shallow copy)
	Mat mat2 = mat1.reshape(0, 1);
	cout << "mat1: \n" << mat1 << endl;
	cout << "mat2: \n" << mat2 << endl;
	// 모양말고 단순히 행렬의 행크기 바꾸고싶으면 Mat::reszie()씀
	// void Mat::(resize(size_t sz); void Mat::resize(size_t sz, const Sclar& s); sz: 새로운행갯수, s: 새롭게추가될떄 초기값
	Mat mat3 = mat1.clone();
	mat3.resize(5, 444);
	cout << "mat3: \n" << mat3 << endl;

	//원소 데이터 추가할때 
	mat1.push_back(mat3);
	cout << "mat1.push_back(mat3)'s result: \n" << mat1 << endl;
	//원소 데이터 삭제 void Mat::pop_back(size_t nelems = 1); 제거할행갯수 디폴트는 1 *this행렬 갯수보다 크면 에러
	mat1.pop_back(2);
	cout << "mat1.pop_back(2): \n" << mat1 << endl;





	return 0;
}