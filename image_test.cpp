#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

int main(){
	std::cout << "OpenCV Version: "<< CV_VERSION << std::endl;
	cv :: Mat img;
	cv ::namedWindow("EXAMPLE01", CV_WINDOW_AUTOSIZE);
	
	img = cv::imread("cat.jpg", cv::IMREAD_COLOR);
	if(img.empty()){
		std::cout << "[!] You can not see the cat!" << std::endl;
		return -1;
	}
	cv::imshow("EXAMPLE01", img);
	cv::waitKey(0);
	cv::destroyWindow("EXAMPLE01");
	return 0;
}
