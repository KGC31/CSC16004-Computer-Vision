#include <opencv2/opencv.hpp>
#include <iostream>
#include "sift.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    // Check command line arguments
    if (argc != 5 || strcmp(argv[1], "-sift") != 0) {
        cout << "Usage: <Executable file> -sift <TemplateImagePath> <SceneImagePath> <OutputFilePath>" << endl;
        return -1;
    }

    // Parse command line arguments
    string mode = argv[1];
    string objectImagePath = argv[2];
    string sceneImagePath = argv[3];
    string outputImagePath = argv[4];

    if(mode == "-sift"){
        siftKNNMatcher(objectImagePath, sceneImagePath, outputImagePath);
    }

    return 0;
}
