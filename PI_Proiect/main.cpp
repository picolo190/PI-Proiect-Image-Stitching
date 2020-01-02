#include "functii.h"

#include <string>

int main(void)
{
	string image_name_1("Images/Building_1_1.jpg");
	string image_name_2("Images/Building_1_2.jpg");
	Mat image_1 = imread(image_name_1, IMREAD_UNCHANGED);
	Mat image_2 = imread(image_name_2, IMREAD_UNCHANGED);
	if (image_1.empty() || image_2.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	vector<KeyPoint> kp1 = keyPointDetection(image_1);
	vector<KeyPoint> kp2 = keyPointDetection(image_2);

	Mat descriptor1 = calculateDescriptors(kp1, image_1), descriptor2 = calculateDescriptors(kp2, image_2);

	vector<DMatch> matching_kp = descriptorMatching(descriptor1, descriptor2);

	vector<Point2f> matching_kp1 = extractKp(matching_kp, kp1), matching_kp2 = extractKp(matching_kp, kp2);

	Mat homography = findHomography(matching_kp1, matching_kp2, RANSAC);

	Mat result;

	warpPerspective(image_1, result, homography, Size(image_1.cols + image_2.cols, image_1.rows));

	Mat half(result, Rect(0, 0, image_2.cols, image_2.rows));

	image_2.copyTo(half);
	/*
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
	*/
	// display result and save it
	imshow("window", result);

	waitKey(0);
	return 0;
}