#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

/*
	A helper structure that contains the descriptors and the keypoints of an image.
*/
struct descriptorAndKeypoints {
	Mat descriptor;
	vector<KeyPoint> keypoints;
};

/*
	The checkImage method receives an image and checks if it was read corectly
	otherwise the app closes.
*/
void checkImage(Mat img);

/*
	This function detects the keypoints from a given image and computes the descriptors 
	based on the keypoints extracted previously.
*/
descriptorAndKeypoints detectAndCompute(Mat img1, string s);

/*
	The calculateHomography function takes 2 descriptorAndKeypoints as arguments, those represent the descriptors
	and the keypoints for each image. Those descriptors are being matched using the FLANN method. The resulted matches are being filtred:
	the ones > 3 * min_dist are dropped. The homography matrix is then calculated based on the RANSAC method.
*/
Mat calculateHomography(descriptorAndKeypoints img1_kp_desc, descriptorAndKeypoints img2_kp_desc, Mat image_1, Mat image_2);

/*
	The stitchImage receives two images and the homography matrix. It tries to apply the homography to one on those images
	to change the perspective on it so it can be stitched to the second image.
*/
Mat stitchImage(Mat img1, Mat img2, Mat H);

/*
	This function saves the image to a file; it receives an image and a string representing the path
*/
void saveImage(Mat img, string path);