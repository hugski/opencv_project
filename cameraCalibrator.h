#ifndef CAMERACLIBRATOR_H
#define CAMERACLIBRATOR_H

#include <iostream>
#include <vector>

#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class CameraCalibrator {
    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
    //标志opencv 矫正的方式

    cv::Mat map1, map2;
    int flag = 0;
    bool mustInitUndistort = true;

   public:
    /* CameraCalibrator() : flag(0), mustInitUndistort(true) {} */
    CameraCalibrator() = default;

    auto addChessboardPoints(const std::vector<std::string> &filelist,
                             cv::Size &boardSize, std::string windowName = "")
        -> int;

    void addPoints(const std::vector<cv::Point2f> &imageCorners,
                   const std::vector<cv::Point3f> &objectCorners);

    auto calibrate(cv::Size imageSize) -> double;

    void setCalibrationFlag(bool radial8CoeffEnable = false,
                            bool tangentialParamEnable = false);
    auto remap(const cv::Mat &image, cv::Size &outputSize) -> cv::Mat;

    auto getCameraMatrix() -> cv::Mat { return cameraMatrix; };
    auto getDistCoeffs() -> cv::Mat { return distCoeffs; };
};

#endif
