#pragma once

#include <string>
#include <opencv2/core.hpp>

cv::Mat readImage(const std::string& imageName);
void showImage(const cv::Mat& image);
std::string filenameExtension(const std::string& filename);