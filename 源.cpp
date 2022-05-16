#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
void myResizeSmollRGB_1(Mat src, Mat& dst, double k1, double k2) {
	int rowNumber = src.rows;
	int colNumber = src.cols;
	dst.create(rowNumber * k1, colNumber * k2, CV_8UC(src.channels()));
	for (int i = 0; i < dst.rows; i++) {
		uchar* data = dst.ptr<uchar>(i);
		uchar* inputData = src.ptr<uchar>(i / k1);
		for (int j = 0; j < dst.cols * 3; j += 3) {
			data[j] = inputData[int(j / k2)];
			data[j + 1] = inputData[int(j / k2 + 1)];
			data[j + 2] = inputData[int(j / k2 + 2)];
		}
	}
}
void myResizeSmollRGB_2(Mat src, Mat& dst, double k1, double k2) {
	int rowNumber = src.rows;
	int colNumber = src.cols;
	dst.create(rowNumber * k1, colNumber * k2, CV_8UC(src.channels()));
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i / k1, j / k2)[0];
			dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i / k1, j / k2)[1];
			dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i / k1, j / k2)[2];
		}
	}
}

void myResizeMax(Mat src, Mat& dst, double k1, double k2) {
	int rowNumber = src.rows;
	int colNumber = src.cols;
	dst.create(rowNumber * k1, colNumber * k2, CV_8UC(src.channels()));
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i / k1, j / k2)[0];
			dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i / k1, j / k2)[1];
			dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i / k1, j / k2)[2];
		}
	}
}
void level(Mat src, Mat& dst) {
	int rowNumber = src.rows;
	int colNumber = src.cols;
	dst.create(rowNumber, colNumber, CV_8UC(src.channels()));
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, src.rows - j - 1)[0];
			dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, src.rows - j - 1)[1];
			dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, src.rows - j - 1)[2];
		}
	}
}
void vertical(Mat src, Mat& dst) {
	int rowNumber = src.rows;
	int colNumber = src.cols;
	dst.create(rowNumber, colNumber, CV_8UC(src.channels()));
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(src.rows - i - 1, j)[0];
			dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(src.rows - i - 1, j)[1];
			dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(src.rows - i - 1, j)[2];
		}
	}

}
void revolve_inverse(Mat src, Mat& dst, float angle) {
	int rowNumber = src.rows;
	int colNumber = src.cols;
	dst.create(rowNumber * 3, colNumber * 3, CV_8UC(src.channels()));
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			float co, si;
			co = cosf(angle * CV_PI / 180);
			si = sinf(angle * CV_PI / 180);
			int ii, jj;
			ii = i * co - j * si;
			jj = i * si - j * co;
			while (ii < 0 || ii >= src.rows || jj < 0 || jj >= src.cols) {
				if (ii < 0) {
					ii = src.rows + ii;
				}
				if (jj < 0) {
					jj = src.cols + jj;
				}
				if (ii >= src.rows) {
					ii = ii % src.rows;
				}
				if (jj >= src.cols) {
					jj = jj % src.cols;
				}
			}
			dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(ii, jj)[0];
			dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(ii, jj)[1];
			dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(ii, jj)[2];
		}
	}

}
void revolve(Mat src, Mat& dst, float angle) {
	int rowNumber = src.rows;
	int colNumber = src.cols;
	dst.create(rowNumber * 3, colNumber * 3, CV_8UC(src.channels()));
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			float co, si;
			co = cosf(angle * CV_PI / 180);
			si = sinf(angle * CV_PI / 180);
			int ii, jj;
			ii = i * co + j * si;
			jj = j * co - i * si;
			while (ii < 0 || ii >= src.rows || jj < 0 || jj >= src.cols) {
				if (ii < 0) {
					ii = src.rows + ii;
				}
				if (jj < 0) {
					jj = src.cols + jj;
				}
				if (ii >= src.rows) {
					ii = ii % src.rows;
				}
				if (jj >= src.cols) {
					jj = jj % src.cols;
				}
			}
			dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(ii, jj)[0];
			dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(ii, jj)[1];
			dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(ii, jj)[2];
		}
	}

}
int main() {
	Mat inputImage = imread("./images/1.jpg", 1);
	Mat outputImage;
	double k1 = 0.4;
	double k2 = 0.2;
	myResizeSmollRGB_1(inputImage, outputImage, k1, k2);
	imshow("缩小1", outputImage);

	inputImage = imread("./images/1.jpg", 1);
	k1 = 0.3;
	k2 = 0.1;
	myResizeSmollRGB_2(inputImage, outputImage, k1, k2);

	inputImage = imread("./images/2.jpg", 1);
	k1 = 2;
	k2 = 2;
	myResizeMax(inputImage, outputImage, k1, k2);
	imshow("放大", outputImage);

	inputImage = imread("./images/2.jpg", 1);
	level(inputImage, outputImage);

	imshow("水平翻转", outputImage);
	vertical(inputImage, outputImage);

	imshow("垂直翻转", outputImage);
	myResizeSmollRGB_1(inputImage, outputImage, 0.5, 0.5);
	revolve_inverse(inputImage, outputImage, 60);

	imshow("旋转逆", outputImage);
	revolve(inputImage, outputImage, 90);

	imshow("旋转顺", outputImage);
	waitKey();
	return 0;
}