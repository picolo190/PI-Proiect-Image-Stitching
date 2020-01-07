# Image stitching using opencv_contrib library

This repository is an implementation of image stitching algorithm using the opencv contrib version which contains some additional implemented algorithms by the opencv devs. Those algorithms are not included in the basic version of opencv.

## Getting Started

First, it needs the opencv contrib library installed in the pc(it will be linked below, so just download it). Then the IDE need to be set so the linker knows those external references made in the library.


### Installing


### IMPORTANT: make sure the solution platform is set to x64 architecture, as the opencv is build on x64, otherwise the solution won't build.


In Visual Studio there are 3 settings to be made in the project settings:

* ### C/C++ -> General -> Additional Include Directories -> New: the IDE needs to know the path to ..\new_opencv_contrib\install\include in your PC.
* ### Linker -> General -> Additional Library Directories -> New: the IDE needs to know the path to ..\new_opencv_contrib\install\x64\vc\lib in your PC.
* ### Linker -> Input -> Additional Dependencies -> add opencv_world412d.lib to those files.
* ### Also after all those IDE settings are done, the opencv_world412d.dll needs to be added to the project folder (..\PI-Proiect-Image-Stitching\PI_Proiect\).


## Algorithm


The algorithm's goal is to receive two images with a "common" area and to stitch those two images into a single one. It may be easier for the human eye to recognise this matching, but stitching two images with this algorithm attracts a constraint: the user need to input the images in order, as the left image first and the right image second. This order confirms that there is a common zone, known by the user, but also there can be inputed two images with no common area and still representing a sequence. In this case the algorithm doesn't work.


There are some steps followed in order to implement the stitching algorithm:

* ### Detecting the KeyPoints in an image using the SURF method.

This SURF method used to detect the KeyPoints is a popular method implemented in the opencv library. It detects the keypoints based on a *hessian threshold*. To get more keypoints in a image, you need to lower the threshold.

For more information about SURF go to [opencv documentation](https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_feature2d/py_surf_intro/py_surf_intro.html).


* ### Calculating descriptors

Using the same SURF method, the descriptors are computed and extracted based on the previous KeyPoints detected.


* ### FLANN Matching

FLANN(Fast Library for Approximate Nearest Neighbors) finds the best matches for local image features. Those matches are calculated based on the descriptors of the images. After getting those matches, there needs to be a filter applied on them: the distance of the matches needs to be 3 times the min_dist.

For more information about the FLANN matching method visit [OpenCV: Feature Matching with FLANN](https://docs.opencv.org/3.4/d5/d6f/tutorial_feature_flann_matcher.html).


* ### Find the homography between two planes using RANSAC method


RANdom SAmple Consensus (RANSAC) is a general parameter estimation approach designed to cope with a large proportion of outliers in the input data. Basically RANSAC approximates based on the most "good" input values, the ones "odd" are removed from the aproximation.


* [Overview of the RANSAC algorithm.](http://www.cse.yorku.ca/~kosta/CompVis_Notes/ransac.pdf)
* [RANSAC explained.](http://www.cs.tau.ac.il/~turkel/imagepapers/RANSAC4Dummies.pdf)


Using the RANSAC method for approximation, we find the homography matrix, a 3x3 mask. The homography's goal is to rotate an given image to match another image viewed from another perspective.


* [Basic concepts of the homography explained with code.](https://docs.opencv.org/master/d9/dab/tutorial_homography.html)


## Acknowledged errors

The algorithm works only if the user inputs two images matching the description: the two images represents a sequence, so it has a common area and those images are inputed correctly, the first image need to be the one leftmost and the second image needs to be the rightmost. If this description is not matched, then the result is not the one desired.


## Built with

* [OpenCV contrib library](https://drive.google.com/drive/folders/1_wwww4ck7L5x25np1ffpxzM4QktuRXMV)
* [CMake GUI](https://cmake.org/download/)


## Resources and references

[Image Panorama Stitching with OpenCV](https://towardsdatascience.com/image-panorama-stitching-with-opencv-2402bde6b46c)

[Image Stitching with OpenCV](https://www.pyimagesearch.com/2018/12/17/image-stitching-with-opencv-and-python/)

