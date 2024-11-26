#include "opencv2/core.hpp"
#include <self/filter.hpp>

namespace self {

namespace filter {

void box_filter(cv::Mat &image, int ksize) {
    cv::boxFilter(image, image, -1, cv::Size_(ksize,ksize));
}

void gaussian(cv::Mat &image, int ksize) {
    cv::GaussianBlur(image, image, cv::Size_(ksize,ksize), ksize, ksize);
}

void dog(cv::Mat &image, int ksize, int std) {
    cv::Mat beeg;
    cv::Mat smol;
    cv::GaussianBlur(image, beeg, cv::Size_(ksize,ksize), std, std);
    cv::GaussianBlur(image, smol, cv::Size_(2*ksize+1,2*ksize+1), 5*std, 5*std);
    cv::subtract(beeg, smol, image);
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

void bitwise_not(cv::Mat &image) {
    cv::bitwise_not(image, image);
}

void canny(cv::Mat &image) {
    cv::Mat cannyed;
    cv::Canny(image, cannyed, 0, 150);
    cannyed.copyTo(image);
}

void sharpen(cv::Mat &image, int strengh) {
    cv::Mat kernel(3, 3, CV_8S, cv::Scalar(-2));
    kernel.row(0).col(0) = 1;
    kernel.row(0).col(2) = 1;
    kernel.row(1).col(1) = 5;
    kernel.row(2).col(0) = 1;
    kernel.row(2).col(2) = 1;
    cv::filter2D(image, image, -1, kernel*strengh);
}

void median_blur(cv::Mat &image, int ksize) {
    cv::medianBlur(image, image, ksize);
}

void grayscale(cv::Mat &image) {
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    
}

void wow(cv::Mat &image) {
    cv::Mat kernel(3, 3, CV_8S, cv::Scalar(0));
    kernel.row(0).col(0) = 1;
    kernel.row(0).col(2) = 1;
    kernel.row(1).col(1) = -3;
    kernel.row(2).col(0) = 1;
    kernel.row(2).col(2) = 1;
    cv::filter2D(image, image, -1, kernel);
}

}

}
