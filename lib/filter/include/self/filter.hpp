#pragma once

#include <opencv2/opencv.hpp>

namespace self {

namespace filter {

// 1
void box_filter(cv::Mat& image, int ksize);
// 2
void gaussian(cv::Mat& image, int ksize);
// 3
void edge_detect(cv::Mat& image);
// 4
void fry(cv::Mat& image);
// 5
void bitwise_not(cv::Mat &image);
// 6
void canny(cv::Mat &image);
// 7
void sharpen(cv::Mat &image);
// 8
void median_blur(cv::Mat &image, int ksize);
// 9
void grayscale(cv::Mat &image);
// 10
void wow(cv::Mat &image);

} // namespace filter

} // namespace self
