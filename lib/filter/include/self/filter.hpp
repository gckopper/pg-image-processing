#pragma once

#include "opencv2/opencv.hpp"

namespace self {

namespace filter {

void box_filter(cv::Mat& image);
void gaussian(cv::Mat& image);
void edge_detect(cv::Mat& image);
void fry(cv::Mat& image);

} // namespace filter

} // namespace self
