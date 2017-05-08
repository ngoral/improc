#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include "improc.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

std::string getImageName(int argc, char** argv)
{
    return (argc > 2) ? argv[2] : "no_signal.png";
}

bool angleValid(int angle)
{
    return abs(angle) % 45 == 0;
}

int getAngle(int argc, char** argv)
{
    if (argc > 1)
    {
        if (angleValid(std::stoi(argv[1])))
            return std::stoi(argv[1]);
        else
            throw std::runtime_error("Wrong angle `" + std::string(argv[1]) + "'");
    }
    else
        throw std::runtime_error("Could not find angle. Usage: ./rotate angle [image_name] ");
}

double gradToRad(int angle)
{
    return angle / 180.0 * M_PI;
}

double newX(cv::Point pos, double angle, cv::Point center)
{
    return center.x + (pos.x - center.x) * cos(angle) + (pos.y - center.y) * sin(angle);
}

double newY(cv::Point pos, double angle, cv::Point center)
{
    return center.y - (pos.x - center.x) * sin(angle) + (pos.y - center.y) * cos(angle);
}

void updateImage(cv::Mat& image, cv::MatConstIterator_<uchar>& pixel, double angle)
{
    cv::Point center = cv::Point(image.cols / 2, image.rows / 2);
    double x = newX(pixel.pos(), angle, center), y = newY(pixel.pos(), angle, center);

    if (x >= 0 && y >= 0 && x < image.cols && y < image.rows)
    {
        image.at<uchar>(y, x) = *pixel;
    }
}

int newWidth(int originalWidth, int originalHeight, double angle)
{
    return std::abs(originalWidth * std::abs(cos(angle)) + originalHeight * std::abs(sin(angle)));
}

int newHeight(int originalWidth, int originalHeight, double angle)
{
    return abs(originalWidth * std::abs(sin(angle)) + originalHeight * std::abs(cos(angle)));
}
cv::Mat rotate(const cv::Mat& original, double angle)
{
    cv::Mat rotated = cv::Mat::zeros(
                                        newHeight(original.cols, original.rows, angle),
                                        newWidth(original.cols, original.rows, angle),
                                        CV_8UC1
                                    );

    for (auto origPixel = original.begin<uchar>(), end = original.end<uchar>(); origPixel != end; ++origPixel)
    {
        updateImage(rotated, origPixel, angle);
    }

    return rotated;
}

int main(int argc, char** argv)
{
    try
    {
        double angle = gradToRad(getAngle(argc, argv));
        std::string imageName = getImageName(argc, argv);
        cv::Mat image = readImage(imageName);
        cv::Mat rotated = rotate(image, angle);

        showImage(rotated);

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "rotate: " << e.what() << std::endl;
        return 1;
    }
}