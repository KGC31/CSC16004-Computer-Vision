// filter.hpp
/* 
    This file includes the definition of the filter functions for the implementation of the filters
    Filters function structure:
        void <name of the filter> (string <input_file>, string <output_file name>, int <kernel_size>);
*/
#ifndef FILTER_HPP
#define FILTER_HPP

#include "common.hpp"

void medFilter(string inFile, string outFile, int c);

void avgFilter(string inFile, string outFile, int c);

void gaussianFilter(string inFile, string outFile, int c);

#endif