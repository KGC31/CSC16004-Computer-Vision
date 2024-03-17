#include "sift.hpp"

void siftKNNMatcher(string objectImagePath, string sceneImagePath, string outputImagePath){
        // Load images
    Mat templateImage = imread(objectImagePath, IMREAD_GRAYSCALE);
    Mat sceneImage = imread(sceneImagePath, IMREAD_GRAYSCALE);

    // Check if images are loaded successfully
    if (templateImage.empty() || sceneImage.empty()) {
        cout << "Error: Unable to load image(s)" << endl;
        return;
    }

    // Initialize feature detector and descriptor extractor
    Ptr<Feature2D> detector = SIFT::create();
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");

    // Detect keypoints and compute descriptors
    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    detector->detectAndCompute(templateImage, noArray(), keypoints1, descriptors1);
    detector->detectAndCompute(sceneImage, noArray(), keypoints2, descriptors2);

    // Match descriptors
    vector<vector<DMatch>> knnMatches;
    matcher->knnMatch(descriptors1, descriptors2, knnMatches, 2);

    // Filter matches using Lowe's ratio test
    const float ratio_thresh = 0.7f;
    vector<DMatch> goodMatches;
    for (size_t i = 0; i < knnMatches.size(); i++) {
        if (knnMatches[i][0].distance < ratio_thresh * knnMatches[i][1].distance) {
            goodMatches.push_back(knnMatches[i][0]);
        }
    }

    // Draw matches
    Mat imgMatches;
    drawMatches(templateImage, keypoints1, sceneImage, keypoints2, goodMatches, imgMatches, Scalar::all(-1),
                Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // Find homography
    vector<Point2f> obj;
    vector<Point2f> scene;
    for (size_t i = 0; i < goodMatches.size(); i++) {
        obj.push_back(keypoints1[goodMatches[i].queryIdx].pt);
        scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
    }
    Mat H = findHomography(obj, scene, RANSAC);

    // Get corners of the template image
    vector<Point2f> objCorners(4);
    objCorners[0] = Point2f(0, 0);
    objCorners[1] = Point2f((float)templateImage.cols, 0);
    objCorners[2] = Point2f((float)templateImage.cols, (float)templateImage.rows);
    objCorners[3] = Point2f(0, (float)templateImage.rows);

    // Transform corners of the template image to the scene image
    vector<Point2f> sceneCorners(4);
    perspectiveTransform(objCorners, sceneCorners, H);

    // Adjust only the x-coordinate of each corner point to match the width of the template image
    for (int i = 0; i < 4; ++i) {
        sceneCorners[i].x += templateImage.cols;
    }

    // Draw lines around the detected object on the scene image
    line(imgMatches, sceneCorners[0], sceneCorners[1], Scalar(0, 255, 0), 2);
    line(imgMatches, sceneCorners[1], sceneCorners[2], Scalar(0, 255, 0), 2);
    line(imgMatches, sceneCorners[2], sceneCorners[3], Scalar(0, 255, 0), 2);
    line(imgMatches, sceneCorners[3], sceneCorners[0], Scalar(0, 255, 0), 2);

    // Save the result
    imwrite(outputImagePath, imgMatches);
}