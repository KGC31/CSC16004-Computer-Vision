// sift.hpp
/* 
    This file is the include file for the main.cpp that contains the declaration of the Harris key point detection using OpenCV. The file includes the common.hpp file that contains the required libraries.
        void harrisKeyPointDetection (string <input_file>, string <output_file name>;
*/
#ifndef SIFT_HPP
#define SIFT_HPP

#include "common.hpp"

void siftKNNMatcher(string objectImagePath, string sceneImagePath, string outImagePath);

#endif