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

void cornerHarris(Mat img1, string s)
{
	int blockSize = 2;
	int thresh = 200;
	int apertureSize = 3;
	double k = 0.04;
	Mat dst = Mat::zeros(img1.size(), CV_32FC1);
	Mat img1_gray;
	cvtColor(img1, img1_gray, COLOR_BGR2GRAY);
	cornerHarris(img1_gray, dst, blockSize, apertureSize, k);
	Mat dst_norm, dst_norm_scaled;
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);
	for (int i = 0; i < dst_norm.rows; i++)
	{
		for (int j = 0; j < dst_norm.cols; j++)
		{
			if ((int)dst_norm.at<float>(i, j) > thresh)
			{
				circle(dst_norm_scaled, Point(j, i), 5, Scalar(0), 2, 8, 0);
			}
		}
	}
	imshow(s, dst_norm_scaled);
}