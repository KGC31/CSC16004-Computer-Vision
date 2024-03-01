#include "color.hpp"

void rgb2gray(string inputFile, string outputFile){
   // Load a color image
    Mat image = imread(inputFile, IMREAD_COLOR);
    
    // Check if the image is loaded successfully
    if(image.empty()){
        cerr << "Error: Unable to read the input image." << endl;
        return;
    }

    // Convert the color image to grayscale
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // Write the grayscale image to the output file
    imwrite(outputFile, gray);

    cout << "Image converted to grayscale successfully." << endl;
}

void brightness(string inputFile, string outputFile, int c){
    // Load the input image
    Mat image = imread(inputFile);

    // Check if the image is loaded successfully
    if(image.empty()){
        cerr << "Error: Unable to read the input image." << endl;
        return;
    }

    // Apply brightness adjustment
    Mat brightness;
    image.convertTo(brightness, -1, 1, c); //increase the brightness by c

    // Write the brightness adjusted image to the output file
    imwrite(outputFile, brightness);

    cout << "Brightness adjustment applied successfully." << endl;
}

void contrast(string inputFile, string outputFile, int c){
    // Load the input image
    Mat image = imread(inputFile);

    // Check if the image is loaded successfully
    if(image.empty()){
        cerr << "Error: Unable to read the input image." << endl;
        return;
    }

    // Apply contrast adjustment
    Mat contrast;
    image.convertTo(contrast, -1, c, 0);

    // Write the contrast adjusted image to the output file
    imwrite(outputFile, contrast);

    cout << "Contrast adjustment applied successfully." << endl;
}
