#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/calib3d.hpp>
//
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <stdio.h>

#define matrix_width 8
#define matrix_height 8
#define squareSize 1

int main(){
	//step1
	int i, j, numSquares = matrix_width*matrix_height;

	std :: vector< std :: vector< cv :: Point3f>> object_points; //real world
	std :: vector< std :: vector< cv :: Point2f>> image_points; //image

	std :: vector< cv :: Point2f> corners;

	cv :: Size board_sz = cv:: Size(matrix_width, matrix_height);
	std :: vector< cv:: Point3f> obj;

	cv :: Mat img;
	cv :: Mat gray_img;
		
	cv :: namedWindow("win01", CV_WINDOW_AUTOSIZE);
	img = cv::imread("chess4.png", cv:: IMREAD_COLOR);
	
	if(img.empty()){
		std::cout << "[!] You can not see the picture!" << std::endl;
		return -1;
	}

	//chess board test
	
	bool found = cv:: findChessboardCorners(img, board_sz , corners, cv :: CALIB_CB_ADAPTIVE_THRESH | cv :: CALIB_CB_FILTER_QUADS);
	
	if(found){
		cv :: cvtColor(img, gray_img, cv:: COLOR_BGR2GRAY);
		cv :: cornerSubPix(gray_img, corners, cv:: Size(11,11), cv:: Size(-1, -1), cv:: TermCriteria(cv:: TermCriteria::EPS + cv:: TermCriteria::MAX_ITER, 30, 0.01));
		cv:: drawChessboardCorners(img, board_sz, corners, found);
	}
	
	/*
	for( i=0;i<matrix_width;i++){
		for( j=0;j<matrix_height;j++){
			obj.push_back(cv::Point3f(j*squareSize,i*squareSize,0));
		}
	}
	*/
	/*
	for(i=0; i<numSquares ;i++){
		obj.push_back(cv:: Point3f(i/matrix_height, i%matrix_width, 0.0f));
	}
	*/

	for(i=0;i<matrix_height;i++){
		for( int j=0;j<matrix_width;j++)
			obj.push_back(cv:: Point3f(float(j*squareSize),float(i*squareSize), 0.0f));
	}
	
	if(found){
		image_points.push_back(corners);
		object_points.push_back(obj);
	}
	else{
		std:: cout<<"Corners not found!"<< std:: endl;
	}
	
	
	//step2
	//cv :: Mat intrinsic = cv :: Mat(3, 3, CV_32FC1);//내부파라미터
	cv :: Mat intrinsic = cv :: Mat(3, 3, CV_64F);
	cv :: Mat distCoeffs;
	distCoeffs = cv :: Mat:: zeros(8, 1, CV_64F);
	//cv :: Mat distCoeffs = cv :: Mat(1, 5, CV_32FC1); //왜곡상수
	//cv :: Mat intrinsic, distCoeffs, R, T;
	std :: vector<cv :: Mat> R, T;

	
	cv :: calibrateCamera(object_points, image_points, img.size(), intrinsic, distCoeffs, R, T);
	
	cv :: Mat imageUndistorted;
	cv :: undistort(img, imageUndistorted, intrinsic, distCoeffs);
	
	cv::imshow("win01", img);
	cv:: imshow("win02", imageUndistorted);
	cv:: waitKey(0);
	
	return 0;
}
