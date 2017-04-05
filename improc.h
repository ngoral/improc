#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

cv::Mat readImage(const std::string& imageName)
{
    cv::Mat image = cv::imread(imageName, cv::IMREAD_GRAYSCALE); //Read the file (grayscale image)
    if (image.empty())                                           //Check for invalid input
        throw std::runtime_error("Could not open or find the image `" + imageName + "'");
    return image;
}

void showImage(const cv::Mat& image)
{
    cv::namedWindow("Change levels", cv::WINDOW_AUTOSIZE);
    cv::imshow("Change levels", image);
    cv::waitKey(0);
}

std::string filenameExtension(const std::string& filename)
{
    size_t dot = filename.rfind('.');
    size_t basename = filename.rfind('/') + 1;
    return (dot != basename) ? filename.substr(dot) : "";
}