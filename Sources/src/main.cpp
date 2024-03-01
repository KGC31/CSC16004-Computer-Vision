// main.cpp
#include <opencv2/opencv.hpp>
#include <string>
#include "../include/filter.hpp"
#include "../include/color.hpp"
#include "../include/edge.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    // Check for the number of arguments
    if (argc != 4 && argc != 5) {
        cerr << "Usage: " << argv[0] << " -rgb2gray <input_file> <output_file>" << endl;
        cerr << "       " << argv[0] << " -brightness <input_file> <output_file> <brightness_value>" << endl;
        cerr << "       " << argv[0] << " -contrast <input_file> <output_file> <contrast_value>" << endl;
        cerr << "       " << argv[0] << " -med <input_file> <output_file> <kernel_size>" << endl;
        cerr << "       " << argv[0] << " -avg <input_file> <output_file> <kernel_size>" << endl;
        cerr << "       " << argv[0] << " -gau <input_file> <output_file> <kernel_size>" << endl;
        cerr << "       " << argv[0] << " -sobel <input_file> <output_file>" << endl;
        cerr << "       " << argv[0] << " -laplace <input_file> <output_file>" << endl;
        return 1;
    }

    // Get the arguments from the command line
    string mode = argv[1];
    string inFile = argv[2];
    string outFile = argv[3];
    int c = 0;

    // Check if there is the re is 5th argument in the command line
    if(argc == 5){
        c = stoi(argv[4]);
    }

    // Check for the input action mode
    if (mode == "-rgb2gray") {
        rgb2gray(inFile, outFile);
    } else if (mode == "-brightness"){
        brightness(inFile, outFile, c);
    } else if(mode == "-contrast"){
        contrast(inFile, outFile, c);
    } else if(mode == "-med"){
        medFilter(inFile, outFile, c);
    } else if(mode == "-avg"){
        avgFilter(inFile, outFile, c);
    } else if(mode == "-gau"){
        gaussianFilter(inFile, outFile, c);
    } else if(mode == "-sobel"){
        sobelEdgeDetection(inFile, outFile);
    } else if(mode == "-laplace"){
        laplaceEdgeDetection(inFile, outFile);
    } else {
        cerr << "Invalid mode" << endl;
        return 1;
    }

    return 0;
}