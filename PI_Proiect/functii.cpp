#include "functii.h"


void keyPointDetection(Mat img1, Mat img2) {
	int minHessian = 400;
	Ptr<SURF> detector = SURF::create(minHessian);
	std::vector<KeyPoint> keypoints1, keypoints2;
	detector->detect(img1, keypoints1);
	detector->detect(img2, keypoints2);
	//-- Draw keypoints
	Mat img_keypoints1, img_keypoints2;
	drawKeypoints(img1, keypoints1, img_keypoints1);
	drawKeypoints(img2, keypoints2, img_keypoints2);
	//-- Show detected (drawn) keypoints
	imshow("SURF Keypoints1", img_keypoints1);
	imshow("SURF Keypoints2", img_keypoints2);
}