#include "edge.hpp"

void sobelEdgeDetection(string inputFile, string outputFile){
     // Load the input image
    Mat image = imread(inputFile, IMREAD_GRAYSCALE);

    // Check if the image is loaded successfully
    if (image.empty()) {
        cerr << "Error: Unable to read the input image." << endl;
        return;
    }

    // Apply Sobel edge detection
    Mat sobelX, sobelY;
    Sobel(image, sobelX, CV_16S, 1, 0, 3);
    Sobel(image, sobelY, CV_16S, 0, 1, 3);

    // Convert the result back to CV_8U
    Mat sobelX_abs, sobelY_abs;
    convertScaleAbs(sobelX, sobelX_abs);
    convertScaleAbs(sobelY, sobelY_abs);

    // Combine the gradient images
    Mat gradient;
    addWeighted(sobelX_abs, 0.5, sobelY_abs, 0.5, 0, gradient);

    // Write the result to the output file
    imwrite(outputFile, gradient);

    cout << "Edge detection using Sobel operator completed successfully." << endl;
}

void laplaceEdgeDetection(string inputFile, string outputFile) {
    // Load the input image
    Mat image = imread(inputFile, IMREAD_GRAYSCALE);

    // Check if the image is loaded successfully
    if (image.empty()) {
        cerr << "Error: Unable to read the input image." << endl;
        return;
    }

    // Apply Laplace edge detection
    Mat laplace;
    Laplacian(image, laplace, CV_16S, 3);

    // Convert the result back to CV_8U
    Mat laplace_abs;
    convertScaleAbs(laplace, laplace_abs);

    // Write the result to the output file
    imwrite(outputFile, laplace_abs);

    cout << "Laplace edge detection completed successfully." << endl;
}
