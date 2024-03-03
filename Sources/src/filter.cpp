// filter.cpp
#include "filter.hpp"

void medFilter(string inFile, string outFile, int kernelSize) {
    // Read the input image
    Mat img = imread(inFile);

    // Check if the image is empty
    if (img.empty()) {
        cerr << "Error: Unable to read the input image." << endl;
        return;
    }

    // Create a result matrix with the same size and type as the input image
    Mat median = Mat::zeros(img.size(), img.type());

    // Split the input image into color channels
    vector<Mat> channels;
    split(img, channels);

    // Apply median filtering to each color channel separately
    for (int c = 0; c < img.channels(); ++c) {
        Mat channel = channels[c];

        // Iterate over each pixel of the channel
        for (int i = 0; i < channel.rows; ++i) {
            for (int j = 0; j < channel.cols; ++j) {
                vector<int> values; // Store pixel values in the kernel

                // Iterate over each pixel in the kernel neighborhood
                for (int m = -kernelSize / 2; m <= kernelSize / 2; ++m) {
                    for (int n = -kernelSize / 2; n <= kernelSize / 2; ++n) {
                        // Get pixel value at (i + m, j + n)
                        int row = min(max(i + m, 0), channel.rows - 1); // Ensure within image bounds
                        int col = min(max(j + n, 0), channel.cols - 1);
                        values.push_back(channel.at<uchar>(row, col));
                    }
                }

                // Sort the pixel values
                sort(values.begin(), values.end());

                // Get the median value
                int medianIndex = values.size() / 2;
                int medianValue = values[medianIndex];

                // Set the median value to the corresponding pixel in the result matrix
                median.at<Vec3b>(i, j)[c] = medianValue;
            }
        }
    }

    // Write the result to the output file
    imwrite(outFile, median);
    cout << "Apply median filter successfully." << endl;
}


void avgFilter(string inFile, string outFile, int kernelSize) {
    // Read the input image
    Mat img = imread(inFile);

    // Check if the image is empty
    if (img.empty()) {
        cerr << "Error: Unable to read the input image." << endl;
        return;
    }

    // Create the result image
    Mat result(img.size(), img.type());

    // Apply the average filter
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            // Calculate the sum of pixel values in the kernel neighborhood
            Vec3f sum = Vec3f(0.0, 0.0, 0.0);
            int count = 0;

            for (int m = -kernelSize / 2; m <= kernelSize / 2; ++m) {
                for (int n = -kernelSize / 2; n <= kernelSize / 2; ++n) {
                    int row = i + m;
                    int col = j + n;

                    // Check if the pixel is within the image boundaries
                    if (row >= 0 && row < img.rows && col >= 0 && col < img.cols) {
                        sum += img.at<Vec3b>(row, col);
                        ++count;
                    }
                }
            }

            // Compute the average value for each channel
            Vec3f average = sum / static_cast<float>(count);

            // Set the average value to the corresponding pixel in the result matrix
            result.at<Vec3b>(i, j) = average;
        }
    }

    // Write the filtered image to the output file
    imwrite(outFile, result);

    cout << "Average filter applied successfully." << endl;
}

void gaussianFilter(string inFile, string outFile, int kernelSize) {
    // Read the input image
    Mat img = imread(inFile);

    // Check if the image is empty
    if (img.empty()) {
        cerr << "Error: Unable to read the input image." << endl;
        return;
    }

    // Create the result image
    Mat result(img.size(), img.type());

    // Define the Gaussian kernel
    float sigma = 0.3 * ((kernelSize - 1) * 0.5 - 1) + 0.8;
    Mat kernel = getGaussianKernel(kernelSize, sigma, CV_32F);
    Mat kernel2D = kernel * kernel.t();

    // Apply the Gaussian filter
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            // Variables to store the sum of pixel values in the kernel neighborhood
            float sumB = 0, sumG = 0, sumR = 0;

            // Iterate over the kernel neighborhood
            for (int m = -kernelSize / 2; m <= kernelSize / 2; ++m) {
                for (int n = -kernelSize / 2; n <= kernelSize / 2; ++n) {
                    int row = i + m;
                    int col = j + n;

                    // Check if the pixel is within the image boundaries
                    if (row >= 0 && row < img.rows && col >= 0 && col < img.cols) {
                        // Accumulate pixel values weighted by the Gaussian kernel
                        Vec3b pixel = img.at<Vec3b>(row, col);
                        float weight = kernel2D.at<float>(m + kernelSize / 2, n + kernelSize / 2);
                        sumB += pixel[0] * weight;
                        sumG += pixel[1] * weight;
                        sumR += pixel[2] * weight;
                    }
                }
            }

            // Set the weighted sum to the corresponding pixel in the result matrix
            result.at<Vec3b>(i, j) = Vec3b(sumB, sumG, sumR);
        }
    }

    // Write the filtered image to the output file
    imwrite(outFile, result);

    cout << "Gaussian filter applied successfully." << endl;
}