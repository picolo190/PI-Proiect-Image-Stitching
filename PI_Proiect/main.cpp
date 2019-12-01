#include "functii.h"

#include <string>

int main(void)
{
	string image_name_1("Images/Building_1.jpg");
	string image_name_2("Images/Building_2.jpg");
	Mat image_1 = imread(image_name_1, CV_LOAD_IMAGE_COLOR);
	Mat image_2 = imread(image_name_2, CV_LOAD_IMAGE_COLOR);
	if (image_1.empty() || image_2.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("img", image_1);
	
	imshow("img2", image_2);
	
	waitKey(0);
	return 0;
}