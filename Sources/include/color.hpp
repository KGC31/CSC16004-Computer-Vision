// color.hpp
/* 
    This file includes the definition of the functions for the implementation of 
    image processing with brightness, contrast and convert the image to grayscale
        void rgb2gray(string <input_file>, string <output_file>);
        void brightness(string <input_file>, string <output_file>, int <brightness_scale>);
        void contrast(string <input_file>, string <output_file>, int <contrast_scale>);
*/
#ifndef COLOR_HPP
#define COLOR_HPP

#include "common.hpp"

void rgb2gray(string inputFile, string outputFile);

void brightness(string inputFile, string outputFile, int c);

void contrast(string inputFile, string outputFile, int c);

#endif