#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void onMouse(int event, int x, int y, int flags, void *param) {
    cv::Mat *im = reinterpret_cast<cv::Mat*>(param);

    switch (event) {
        case cv::EVENT_LBUTTONDOWN:
            std::cout << "at (" << x << "," << y << ") value is: "
                      << static_cast<int>(im->at<uchar>(cv::Point(x, y)))
                      << std::endl;
            break; }
}
auto main() -> int {
    cv::Mat image;
    std::cout << "This image is " << image.rows << "x " << image.cols
              << std::endl;

    image = cv::imread("bench2.jpg", cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        std::cout << "Error reading image..." << std::endl;

        return 0;
    }
    std::cout << "This image is " << image.rows << "x " << image.cols
              << std::endl;
    std::cout << "This image has " << image.channels() << " channels(s)"
              << std::endl;

    cv::namedWindow("original Image");
    cv::imshow("original image", image);

    cv::setMouseCallback("original Image", onMouse,
                         reinterpret_cast<void *>(&image));

    cv::Mat result;
    cv::flip(image, result, 1);
    cv::namedWindow("Output image");
    cv::imshow("Output Image", result);
    cv::waitKey(0);

    cv::namedWindow("Drawing on an image");
    cv::circle(image, cv::Point(155, 110), 65, 0, 3);
    cv::imshow("Drawing on an Image", image);
    cv::waitKey(0);
}
