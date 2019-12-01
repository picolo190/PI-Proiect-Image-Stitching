#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>
#include "Complex.h"

using namespace std;
using namespace cv;

/* 0: Binary
	 1: Binary Inverted
	 2: Threshold Truncated
	 3: Threshold to Zero
	 4: Threshold to Zero Inverted
   */
int threshold_type = 0;

unsigned char* negateImage(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w*h];
	cv::Mat inMat(h, w, CV_8UC1, img);
	cv::Mat negateMat(h, w, CV_8UC1, result);
	cv::bitwise_not(inMat, negateMat);
	return result;
}

int main(void)
{
	string imageName("Images/File_Bikesgray.jpg");
	Mat image = imread(imageName, CV_8UC1), dst;
	Mat hist;

	//image.data = negateImage(image.data, image.size().width,image.size().height);

	//Threshold op
	threshold(image, dst, 127, 255, threshold_type);

	/*
	//Create hist
	int histSize= 64;
	calcHist(&image, 1, 0, Mat(),  hist, 1, &histSize, 0);

	Mat histImage = Mat::ones(200, 320, CV_8U) * 255;
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, CV_32F);

	histImage = Scalar::all(255);
	int binW = cvRound((double)histImage.cols / histSize);
	for (int i = 0; i < histSize; i++)
	{
		rectangle(histImage, Point(i*binW, histImage.rows), Point((i + 1)*binW, histImage.rows - cvRound(hist.at<float>(i))), Scalar::all(0), -1, 8, 0);
	}
	*/

	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	//namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	//imshow("hist", histImage);                // Show our image inside it.
	//namedWindow("Disp", WINDOW_AUTOSIZE);
	imshow("img", dst);
	waitKey(0);

	return 0;
}