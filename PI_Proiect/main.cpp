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
	imshow("img", image_1);
	imshow("img2", image_2);

	vector<KeyPoint> kp_1 = cornerHarris_new(image_1, "corner1");

	vector<KeyPoint> kp_2 = cornerHarris_new(image_2, "corner2");
	//keyPointDetection(image_1, image_2);

	waitKey(0);
	return 0;
}