#include "edge.hpp"

void sobelEdgeDetection(string inputFile, string outputFile) {
    // Load the input img with grayscale
    Mat img = imread(inputFile, IMREAD_GRAYSCALE);

    // Check if the img is loaded successfully
    if (img.empty()) {
        cerr << "Error: Unable to read the input img." << endl;
        return;
    }

    Mat sobel(img.rows, img.cols, CV_32F);

    // Create gradient matrices to store gradients in x and y directions
    Mat gradientX(img.rows, img.cols, CV_32F);
    Mat gradientY(img.rows, img.cols, CV_32F);

    // Define Sobel kernels
    float sobelKernelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    float sobelKernelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Apply convolution with Sobel kernels
    for (int y = 1; y < img.rows - 1; ++y) {
        for (int x = 1; x < img.cols - 1; ++x) {
            float sumX = 0, sumY = 0;

            // Compute gradients using Sobel kernels
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    sumX += img.at<uchar>(y + i, x + j) * sobelKernelX[i + 1][j + 1];
                    sumY += img.at<uchar>(y + i, x + j) * sobelKernelY[i + 1][j + 1];
                }
            }

            // Calculate gradient magnitude using the Euclidean distance formula
            float magnitude = sqrt(sumX * sumX + sumY * sumY);

            // Store the gradient magnitude in the sobel matrix
            sobel.at<float>(y, x) = magnitude;
        }
    }

    // Write the result to the output file
    imwrite(outputFile, sobel);

    cout << "Edge detection using Sobel operator completed successfully." << endl;
}

void laplaceEdgeDetection(string inputFile, string outputFile) {
    // Load the input img
    Mat img = imread(inputFile, IMREAD_GRAYSCALE);

    // Check if the img is loaded successfully
    if (img.empty()) {
        cerr << "Error: Unable to read the input img." << endl;
        return;
    }

    // Define Laplacian kernel
    float laplacianKernel[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};

    // Apply convolution with Laplacian kernel
    Mat laplace(img.size(), CV_32F);
    for (int y = 1; y < img.rows - 1; ++y) {
        for (int x = 1; x < img.cols - 1; ++x) {
            float sum = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    sum += img.at<uchar>(y + i, x + j) * laplacianKernel[i + 1][j + 1];
                }
            }
            laplace.at<float>(y, x) = sum;
        }
    }

    // Write the result to the output file
    imwrite(outputFile, laplace);

    cout << "Laplace edge detection completed successfully." << endl;
}
