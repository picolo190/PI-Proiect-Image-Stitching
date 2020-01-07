# Image stitching using opencv_contrib library

This repository is an implementation of image stitching algorithm using the opencv contrib version which contains some additional implemented algorithms by the opencv devs. Those algorithms are not included in the basic version of opencv.

## Getting Started

First, it needs the opencv contrib library installed in the pc(it will be linked below, so just download it). Then the IDE need to be set so the linker knows those external references made in the library.

In Visual Studio there are 3 settings to be made in the project settings:

* C/C++ -> General -> Additional Include Directories -> New: the IDE needs to know the path to ..\new_opencv_contrib\install\include in your PC.
* Linker -> General -> Additional Library Directories -> New: the IDE needs to know the path to ..\new_opencv_contrib\install\x64\vc\lib in your PC.
* Linker -> Input -> Additional Dependencies -> add opencv_world412d.lib to those files.
* Also after all those IDE settings are done, the opencv_world412d.dll needs to be added to the project folder (..\PI-Proiect-Image-Stitching\PI_Proiect\).

### IMPORTANT: make sure the solution platform is set to x64 architecture, as the opencv is build on x64, otherwise the solution won't build.

## Algorithm

## Installing

## Built with

## Resources and references
