#include <self/filter.hpp>

namespace self {

namespace filter {

void box_filter(cv::Mat &image) {
       
}

void gaussian(cv::Mat &image) {

}

void edge_detect(cv::Mat &image) {
    cv::Mat kernel(3, 3, CV_8S, cv::Scalar(-1));
    kernel.row(1).col(1) = 8;
    cv::filter2D(image, image, -1, kernel);
}

void fry(cv::Mat &image) {
    cv::Mat kernel(3, 3, CV_8U, cv::Scalar(-1));
    kernel.row(1).col(1) = 8;
    cv::filter2D(image, image, -1, kernel);
}

}

}
