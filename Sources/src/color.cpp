#include "color.hpp"

void rgb2gray(string inputFile, string outputFile){
   // Load a color img
    Mat img = imread(inputFile, IMREAD_COLOR);
    
    // Check if the img is loaded successfully
    if(img.empty()){
        cerr << "Error: Unable to read the input img." << endl;
        return;
    }

    // Assign new img with the size of the input img, and the type of CV_8UC1 (grayscale img type)
    Mat gray(img.rows, img.cols, CV_8UC1);

    // Convert the color img to grayscale
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            // Get the RGB pixel values
            Vec3b rgb = img.at<Vec3b>(i, j);
            // Compute the grayscale intensity value (average of RGB channels)
            uchar intensity = (rgb[0] + rgb[1] + rgb[2]) / 3;
            // Set the grayscale pixel value
            gray.at<uchar>(i, j) = intensity;
        }
    }

    // Write the grayscale img to the output file
    imwrite(outputFile, gray);

    cout << "img converted to grayscale successfully." << endl;
}

void brightness(string inputFile, string outputFile, int c){
    // Load the input img
    Mat img = imread(inputFile);

    // Check if the img is loaded successfully
    if(img.empty()){
        cerr << "Error: Unable to read the input img." << endl;
        return;
    }

    // Create zero-like img with the size of the input img
    Mat brightness(img.rows, img.cols, img.type(), Scalar(0));

    // Increase brightness by c
    for (int i = 0; i < img.rows; i++){
        for (int j = 0; j < img.cols; j++){
            for (int t = 0; t < 3; t++){
                brightness.at<Vec3b>(i, j)[t] = std::max(std::min(img.at<Vec3b>(i, j)[t] + c, 255), 0);
            }
        }
    }

    // Write the brightness adjusted img to the output file
    imwrite(outputFile, brightness);

    cout << "Brightness adjustment applied successfully." << endl;
}

void contrast(string inputFile, string outputFile, int c){
    // Load the input img
    Mat img = imread(inputFile);

    // Check if the img is loaded successfully
    if(img.empty()){
        cerr << "Error: Unable to read the input img." << endl;
        return;
    }

    // Create zero-like img with the size of the input img
    Mat contrast(img.rows, img.cols, img.type(), Scalar(0));

    // Multiply contrast by c
    for (int i = 0; i < img.rows; i++){
        for (int j = 0; j < img.cols; j++){
            for (int t = 0; t < 3; t++){
                contrast.at<Vec3b>(i, j)[t] = std::max(std::min(img.at<Vec3b>(i, j)[t] * c, 255), 0);
            }
        }
    }

    // Write the contrast adjusted img to the output file
    imwrite(outputFile, contrast);

    cout << "Contrast adjustment applied successfully." << endl;
}
