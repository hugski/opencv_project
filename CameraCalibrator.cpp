#include "cameraCalibrator.h"

auto CameraCalibrator::addChessboardPoints(
    const std::vector<std::string>& filelist, cv::Size& boardSize,
    std::string windowName) -> int {
    std::vector<cv::Point2f> imageCorners;
    std::vector<cv::Point3f> objectCorners;

    for (int i = 0; i < boardSize.height; i++) {
        for (int j = 0; j < boardSize.width; j++) {
            objectCorners.emplace_back(cv::Point3f(i, j, 0.0F));
        }
    }

    cv::Mat image;
    int success = 0;
    /* for (int i = 0; i < filelist.size(); i++) { */
    for (auto file : filelist) {
        std::cout << file << std::endl;
        image = cv::imread(file, 0);
        bool found = cv::findChessboardCorners(image, boardSize, imageCorners);
        if (found) {
            cv::cornerSubPix(image, imageCorners, cv::Size(5, 5),
                             cv::Size(-1, -1),
                             cv::TermCriteria(cv::TermCriteria::MAX_ITER +
                                                  cv::TermCriteria::EPS,
                                              30, 0.1));
            if (imageCorners.size() == boardSize.area()) {
                addPoints(imageCorners, objectCorners);
                success++;
            }
        }

        if (windowName.length() > 0 &&
            imageCorners.size() == boardSize.area()) {
            cv::drawChessboardCorners(image, boardSize, imageCorners, found);
            cv::imshow(windowName, image);
            cv::waitKey(100);
        }
    }

    return success;
}

void CameraCalibrator::addPoints(const std::vector<cv::Point2f>& imageCorners, const std::vector<cv::Point3f>& objectCorners) {
    imagePoints.push_back(imageCorners);
    objectPoints.push_back(objectCorners);
}

double CameraCalibrator::calibrate(const cv::Size imageSize) {
    mustInitUndistort = true;
    std::vector<cv::Mat> rvecs, tvecs;
    return cv::calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, flag);
}

cv::Mat CameraCalibrator::remap(const cv::Mat &image, cv::Size &outputSize) {
    cv::Mat undistored;

    if(outputSize.height == -1) {
        outputSize = image.size();
    }
    if(mustInitUndistort) {
        cv::initUndistortRectifyMap(
                cameraMatrix,
                distCoeffs,
                cv::Mat(),
                cv::Mat(),
                outputSize,
                CV_32FC1,
                map1, map2
                );
        mustInitUndistort = false;
    }

    cv::remap(image, undistored, map1, map2, cv::INTER_LINEAR);

    return undistored;
}

void CameraCalibrator::setCalibrationFlag(bool radial8CoeffEnabled, bool tangentialParamEnabled) {

    // Set the flag used in cv::calibrateCamera()
    flag = 0;
    if (!tangentialParamEnabled) flag += cv::CALIB_ZERO_TANGENT_DIST;
	if (radial8CoeffEnabled) flag += cv::CALIB_RATIONAL_MODEL;
}

