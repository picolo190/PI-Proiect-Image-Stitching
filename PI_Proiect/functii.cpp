#include "functii.h"

void checkImage(Mat img) 
{
	//**** check the images read ****
	if (img.empty())
	{
		cout << "Could not open or find the image" << endl;
		exit(-1);
	}
}

descriptorAndKeypoints detectAndCompute(Mat img1, string s)
{
	//Set the hessian threshold; The higher it is, the less keypoints get detected
	int minHessian = 400;

	descriptorAndKeypoints result;
	
	//Create a surf instance
	Ptr<SURF> surf_method = SURF::create(minHessian);

	surf_method->detect(img1, result.keypoints);

	//Create the mat which contains the image represented with keypoints
	Mat img_with_keypoints;
	drawKeypoints(img1, result.keypoints, img_with_keypoints);

	//Save the image with kp
	saveImage(img_with_keypoints, s);

	surf_method->compute(img1, result.keypoints, result.descriptor);

	return result;	
}

Mat calculateHomography(descriptorAndKeypoints img1_kp_desc, descriptorAndKeypoints img2_kp_desc, Mat image_1, Mat image_2)
{
	//Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match(img1_kp_desc.descriptor, img2_kp_desc.descriptor, matches);

	//Initialize the min max dist
	double max_dist = 0;
	double min_dist = 100;

	//--Quick calculation of min-max distances between keypoints
	for (int i = 0; i < img1_kp_desc.descriptor.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist)
		{ 
			min_dist = dist; 
		}
		if (dist > max_dist)
		{
			max_dist = dist;
		}
	}

	cout << "-- Max dist :" << max_dist << endl;
	cout << "-- Min dist :" << min_dist << endl;

	//--Use only "good" matches (i.e. whose distance is less than 3 X min_dist )
	vector<DMatch> good_matches;

	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	vector< Point2f > img1_points;
	vector< Point2f > img2_points;

	Mat image_with_kp1, image_with_kp2;
	image_1.copyTo(image_with_kp1);
	image_2.copyTo(image_with_kp2);

	vector<KeyPoint> kp1, kp2;

	for (int i = 0; i < good_matches.size(); i++)
	{
		//--Get the keypoints from the good matches
		img1_points.push_back(img1_kp_desc.keypoints[good_matches[i].queryIdx].pt);
		img2_points.push_back(img2_kp_desc.keypoints[good_matches[i].trainIdx].pt);

		//Get the keypoints in a new vector
		kp1.push_back(img1_kp_desc.keypoints[good_matches[i].queryIdx]);
		kp2.push_back(img2_kp_desc.keypoints[good_matches[i].trainIdx]);
	}

	//Draw the good keypoints on the images
	drawKeypoints(image_with_kp1, kp1, image_with_kp1);
	drawKeypoints(image_with_kp2, kp2, image_with_kp2);

	//Save the images with good keypoints
	saveImage(image_with_kp1, "Images/img1_with_good_kp.png");
	saveImage(image_with_kp2, "Images/img2_with_good_kp.png");

	Mat homography = findHomography(img2_points, img1_points, RANSAC);

	return homography;
}

Mat stitchImage(Mat img1, Mat img2, Mat H)
{
	Mat result;

	warpPerspective(img2, result, H, Size(img1.cols + img2.cols, img1.rows));

	Mat half(result, Rect(0, 0, img2.cols, img2.rows));

	img1.copyTo(half);

	// vector with all non-black point positions
	vector<Point> nonBlackList;
	nonBlackList.reserve(result.rows*result.cols);

	// add all non-black points to the vector
	// there are more efficient ways to iterate through the image
	for (int j = 0; j < result.rows; ++j)
	{
		for (int i = 0; i < result.cols; ++i)
		{
			// if not black: add to the list
			if (result.at<Vec3b>(j, i) != Vec3b(0, 0, 0))
			{
				nonBlackList.push_back(Point(i, j));
			}
		}
	}

	// create bounding rect around those points
	Rect bb = boundingRect(nonBlackList);

	return result(bb);
}

void saveImage(Mat img, string path)
{
	bool success = imwrite(path, img);

	if (!success)
	{
		cout << "\nThe image set to be saved at the path:" << path << " was not successfuly saved.";
	}
}