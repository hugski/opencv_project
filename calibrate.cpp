#include <iostream>
#include <iomanip>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

#include "cameraCalibrator.h"

auto main() -> int {
    cv::Mat image;
    std::vector<std::string> filelist;

    for(int i = 1; i <= 27; i++) {
        std::stringstream str;
        str << "chessboards/chessboard" << std::setw(2) << std::setfill('0') << i << ".jpg";
        std::cout << str.str() << std::endl;

        filelist.push_back(str.str());
        image = cv::imread(str.str(), 0);

        cv::imshow("Board Image", image);
        cv::waitKey(100);
    }

    CameraCalibrator cameraCalibrator;

    cv::Size boardSize(10, 10);
    cameraCalibrator.addChessboardPoints(filelist, boardSize, "Detected points");

    cameraCalibrator.setCalibrationFlag(true, true);
    cameraCalibrator.calibrate(image.size());

    image = cv::imread(filelist[14], 0);
    cv::Size newSize(static_cast<int>(image.cols * 1.5), static_cast<int>(image.rows * 1.5));
    cv::Mat uImage = cameraCalibrator.remap(image, newSize);

    cv::Mat cameraMatrix = cameraCalibrator.getCameraMatrix();

    std::cout <<  "内参矩阵: " << cameraMatrix.rows << "x" << cameraMatrix.cols << std::endl;;
    std::cout << cameraMatrix.at<double>(0,0) << cameraMatrix.at<double>(0,1) << cameraMatrix.at<double>(0,2) << std::endl;
    std::cout << cameraMatrix.at<double>(1,0) << cameraMatrix.at<double>(1,1) << cameraMatrix.at<double>(1,2) << std::endl;
    std::cout << cameraMatrix.at<double>(2,0) << cameraMatrix.at<double>(2,1) << cameraMatrix.at<double>(2,2) << std::endl;

    cv::namedWindow("Original Image");
    cv::imshow("Original Image", image);

	cv::namedWindow("Undistorted Image");
    cv::imshow("Undistorted Image", uImage);

	// Store everything in a xml file
	cv::FileStorage fs("calib.xml", cv::FileStorage::WRITE);
	fs << "Intrinsic" << cameraMatrix;
	fs << "Distortion" << cameraCalibrator.getDistCoeffs();

	cv::waitKey();
	return 0;
}















