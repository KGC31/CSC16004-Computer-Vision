// filter.cpp
#include "filter.hpp"


void medFilter(string inFile, string outFile, int c){
    // Read the input file image with image path
    Mat img = imread(inFile, IMREAD_COLOR);

    // Return if the image is empty
    if (img.empty()) {
        cerr << "Error: Unable to read the input image." << endl;
        return;
    }

    // Create image after change the brightness
    Mat median;
    medianBlur(img, median, c);
    imwrite(outFile, median);
    cout << "Apply median filter successfully." << endl;
}

void avgFilter(string inFile, string outFile, int c){
    // Read the input file image with image path
    Mat img = imread(inFile, IMREAD_COLOR);

    // Return if the image is empty
    if (img.empty()) {
        cerr << "Error: Unable to read the input image." << endl;
        return;
    }

    // Create image after change the brightness
    Mat average;
    blur(img, average, Size(c, c));
    imwrite(outFile, average);
    cout << "Apply average filter successfully." << endl;
}

void gaussianFilter(string inFile, string outFIle, int c){
    // Read the input file image with image path
    Mat img = imread(inFile, IMREAD_COLOR);

    // Return if the image is empty
    if (img.empty()) {
        cerr << "Error: Unable to read the input image." << endl;
        return;
    }

    // Create image after change the brightness
    Mat guassian;
    GaussianBlur(img, guassian, Size(c, c), 0, 0);
    imwrite(outFIle, guassian);
    cout << "Apply gaussian filter successfully." << endl;
}