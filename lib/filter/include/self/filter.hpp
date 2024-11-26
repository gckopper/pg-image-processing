#pragma once

#include <opencv2/opencv.hpp>

namespace self {

namespace filter {

// 1
void box_filter(cv::Mat& image, int ksize);
// 2
void gaussian(cv::Mat& image, int ksize);
// 3
void dog(cv::Mat &image, int ksize, int std);
// 4
void edge_detect(cv::Mat& image);
// 5
void fry(cv::Mat& image);
// 6
void bitwise_not(cv::Mat &image);
// 7
void canny(cv::Mat &image);
// 8
void sharpen(cv::Mat &image, int strengh);
// 9
void median_blur(cv::Mat &image, int ksize);
// 10
void grayscale(cv::Mat &image);
// 11
void wow(cv::Mat &image);

} // namespace filter

} // namespace self
