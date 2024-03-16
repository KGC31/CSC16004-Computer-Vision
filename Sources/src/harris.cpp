#include "harris.hpp"

//----------------------------------------------------------------
// Compute the gradient of Ix and Iy of the image
void computeGradients(const Mat& inputImage, Mat& gradientX, Mat& gradientY) {
    Sobel(inputImage, gradientX, CV_32F, 1, 0, 3);
    Sobel(inputImage, gradientY, CV_32F, 0, 1, 3);
}

// ----------------------------------------------------------------
// Get the Gaussian window
Mat computeGaussianWindow(int windowSize, double sigma) {
    Mat gaussianWindow = getGaussianKernel(windowSize, sigma, CV_32F);
    return gaussianWindow * gaussianWindow.t();
}

// ----------------------------------------------------------------
void computeStructureTensor(const Mat& gradientX, const Mat& gradientY, const Mat& window, Mat& Mxx, Mat& Myy, Mat& Mxy) {
    Mxx = gradientX.mul(gradientX);
    Myy = gradientY.mul(gradientY);
    Mxy = gradientX.mul(gradientY);
    GaussianBlur(Mxx, Mxx, Size(window.cols, window.rows), 0);
    GaussianBlur(Myy, Myy, Size(window.cols, window.rows), 0);
    GaussianBlur(Mxy, Mxy, Size(window.cols, window.rows), 0);
}

void computeDeterminant(const Mat& Mxx, const Mat& Myy, const Mat& Mxy, Mat& determinant) {
    determinant = Mxx.mul(Myy) - Mxy.mul(Mxy);
}

void computeTrace(const Mat& Mxx, const Mat& Myy, Mat& trace) {
    trace = Mxx + Myy;
}

//----------------------------------------------------------------
void computeHarrisCornerResponse(const Mat& determinant, const Mat& trace, float k, Mat& cornerResponse) {
    // R = detM - k*(traceM)^2
    cornerResponse = determinant - k * trace.mul(trace);
}

// ----------------------------------------------------------------
// Main function for the implementation of Harris Corner Detection
void harrisKeyPointDetection(string inFile, string outFile) {
    float k = 0.04; // Harris parameter
    int windowSize = 3; // Window size for Gaussian smoothing
    double sigma = 1.0; // Sigma for Gaussian smoothing

    Mat img = imread(inFile, IMREAD_COLOR);
    Mat inputImage;
    cvtColor(img, inputImage, COLOR_BGR2GRAY);
    if (inputImage.empty()) {
        cerr << "Error: Unable to read input image: " << inFile << endl;
        return;
    }

    GaussianBlur(inputImage, inputImage, Size(5, 5), 1.0);

    // Compute gradients
    Mat gradientX, gradientY;
    computeGradients(inputImage, gradientX, gradientY);

    // Compute Gaussian window
    Mat window = computeGaussianWindow(windowSize, sigma);

    // Compute structure tensor
    Mat Mxx, Myy, Mxy;
    computeStructureTensor(gradientX, gradientY, window, Mxx, Myy, Mxy);

    // Compute determinant and trace
    Mat determinant, trace;
    computeDeterminant(Mxx, Myy, Mxy, determinant);
    computeTrace(Mxx, Myy, trace);

    // Compute Harris corner response
    Mat cornerResponse;
    computeHarrisCornerResponse(determinant, trace, k, cornerResponse);

    // Thresholding corner response to find keypoints
    double maxVal;
    // Get the local maxmima of the corner response
    minMaxLoc(cornerResponse, nullptr, &maxVal);
    // Find point with large corner response
    threshold(cornerResponse, cornerResponse, 0.1 * maxVal, 255, THRESH_BINARY);


    // Draw keypoints on output image
    Mat outputImage = img.clone();
    for (int y = 0; y < cornerResponse.rows; ++y) {
        for (int x = 0; x < cornerResponse.cols; ++x) {
            if (cornerResponse.at<float>(y, x) != 0) {
                // Change circle color to red (BGR format)
                Scalar color(0, 0, 255);
                // Increase circle size to 5 pixels
                int radius = 5;
                // Draw circle
                circle(outputImage, Point(x, y), radius, color, 1, LINE_AA);
            }
        }
    }

    imwrite(outFile, outputImage);
}
