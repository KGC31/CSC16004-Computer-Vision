// main.cpp
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    // Check for the number of arguments
    if (argc != 4 && argc != 5) {
        cerr << "Usage: " << argv[0] << " -harris <input_file> <output_file>" << endl;
        return 1;
    }

    // Get the arguments from the command line
    string mode = argv[1];
    string inFile = argv[2];
    string outFile = argv[3];
    
    // Check for the input action mode
    if (mode == "-harris") {
    } else {
        cerr << "Invalid mode" << endl;
        return 1;
    }

    return 0;
}