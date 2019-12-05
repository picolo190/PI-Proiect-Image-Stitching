#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

void keyPointDetection(Mat img1 ,Mat img2);