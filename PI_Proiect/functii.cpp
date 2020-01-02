#include "functii.h"


vector<KeyPoint> keyPointDetection(Mat img1)
{
	int minHessian = 400;
	Ptr<SURF> detector = SURF::create(minHessian);
	std::vector<KeyPoint> keypoints;
	detector->detect(img1, keypoints);

	return keypoints;
}

Mat calculateDescriptors(vector<KeyPoint> kp1, Mat gray_image1)
{
	int minHessian = 400;
	Ptr<SURF> detector = SURF::create(minHessian);
	Mat descriptor;

	detector->compute(gray_image1, kp1, descriptor);
	
	return descriptor;
}

vector<DMatch> descriptorMatching(Mat descriptor1, Mat descriptor2)
{
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match(descriptor1, descriptor2, matches);

	double max_dist = 0;
	double min_dist = 100;

	for (int i = 0; i < descriptor1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	vector< DMatch > good_matches;

	for (int i = 0; i < descriptor1.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	return good_matches;
}

vector<Point2f> extractKp(vector<DMatch> matches, vector<KeyPoint> kp)
{
	vector<Point2f> matching_points;

	for (int i = 0; i < matches.size(); i++)
	{
		matching_points.push_back(kp[matches[i].queryIdx].pt);
	}

	return matching_points;
}



/*
	*************************************************

*/
vector<KeyPoint> cornerHarris_new(Mat img1, string s)
{
	int blockSize = 2, apertureSize = 3, thresh = 175;
	double k = 0.04;
	Mat dst = Mat::zeros(img1.size(), CV_32FC1);
	vector<KeyPoint> keypoints;

	//Creating the grayscale image
	Mat img1_gray;
	cvtColor(img1, img1_gray, COLOR_BGR2GRAY);

	//Applying the Harris corner algorithm
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
				KeyPoint aux(i, j, 1);
				keypoints.push_back(aux);
			}
		}
	}

	//Display the image 
	imshow(s, dst_norm_scaled);
	return keypoints;
}