#include "functii.h"

int main(void)
{
	string image_name_1("Images/uni_1.jpeg");
	string image_name_2("Images/uni_2.jpeg");
	Mat image_1 = imread(image_name_1);
	Mat image_2 = imread(image_name_2);

	checkImage(image_1);
	checkImage(image_2);

	Mat gray_image_1, gray_image_2;

	cvtColor(image_1, gray_image_1, COLOR_BGR2GRAY);
	cvtColor(image_2, gray_image_2, COLOR_BGR2GRAY);

	checkImage(gray_image_1);
	checkImage(gray_image_2);

	//Extract the descriptors and keypoints
	descriptorAndKeypoints image1_desc_kp = detectAndCompute(gray_image_1), image2_desc_kp = detectAndCompute(gray_image_2);

	//Calculate the homography
	Mat homography = calculateHomography(image1_desc_kp, image2_desc_kp);

	//Stitch images
	Mat final_image = stitchImage(image_1, image_2, homography);

	//Display the result
	imshow("window", final_image);

	string path("./Images/result2.png");
	saveImage(final_image, path);

	waitKey(0);
	return 0;
}