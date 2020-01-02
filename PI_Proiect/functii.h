#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

vector<KeyPoint> keyPointDetection(Mat img1);
vector<KeyPoint> cornerHarris_new(Mat img1, string s);
Mat calculateDescriptors(vector<KeyPoint> kp1, Mat gray_image1);
vector<DMatch> descriptorMatching(Mat descriptor1, Mat descriptor2);
vector<Point2f> extractKp(vector<DMatch> matches, vector<KeyPoint> kp);
