// edge.hpp
/* 
    This file includes the definition of the functions for the implementation of the edge detection methods
    The structure of the edge detection function is as below:
        void <name>(string <input_file>, string <output_file>);
    All of the edge detection is implemented on the kernel size of 3x3
*/
#ifndef EDGE_HPP
#define EDGE_HPP

#include "common.hpp"

void sobelEdgeDetection(string inputFile, string outputFile);

void laplaceEdgeDetection(string inputFile, string outputFile);

#endif