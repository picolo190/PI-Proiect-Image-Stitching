#include "functii.h"

int main(void)
{
	//Read the images to be stitched
	string image_name_1("Images/Building_1.jpg"), image_name_2("Images/Building_2.jpg");
	Mat image_1 = imread(image_name_1), image_2 = imread(image_name_2);

	checkImage(image_1);
	checkImage(image_2);

	//Create the gray images of the ones read before
	Mat gray_image_1, gray_image_2;
	cvtColor(image_1, gray_image_1, COLOR_BGR2GRAY);
	cvtColor(image_2, gray_image_2, COLOR_BGR2GRAY);

	checkImage(gray_image_1);
	checkImage(gray_image_2);

	string path("Images/");

	//Extract the descriptors and keypoints
	descriptorAndKeypoints image1_desc_kp = detectAndCompute(gray_image_1, path+="img_with_desc1.png"), image2_desc_kp = detectAndCompute(gray_image_2, path += "img_with_desc2.png");

	//Calculate the homography
	Mat homography = calculateHomography(image1_desc_kp, image2_desc_kp, image_1, image_2);

	//Stitch the images
	Mat final_image = stitchImage(image_1, image_2, homography);

	//Display the result
	imshow("window", final_image);

	//Save the image as a file
	bool ok = false;
	

	while (!ok) 
	{
		string aux;
		cout << "\nEnter the name of the file to contain the new image:";
		cin >> aux;
		if (aux != "")
		{
			path += aux;
			path += ".png";
			ok = true;
		}
	}

	saveImage(final_image, path);

	waitKey(0);
	return 0;
}