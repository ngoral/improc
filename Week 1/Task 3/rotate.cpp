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
    return abs(angle) == 45 || abs(angle) == 90 || abs(angle) == 180 || abs(angle) == 360;
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

double newX(cv::Point pos, double angle)
{
    return pos.x * cos(angle) + pos.y * sin(angle);
}

double newY(cv::Point pos, double angle)
{
    return -pos.x * sin(angle) + pos.y * cos(angle);
}

void updateImage(cv::Mat& image, cv::MatConstIterator_<uchar>& pixel, double angle)
{
    double x = newX(pixel.pos(), angle), y = newY(pixel.pos(), angle);

        //std::cout << pixel.pos().x << pixel.pos().y << std::endl;
        //std::cout << x << y << std::endl;

    if (x >= 0 && y >= 0 && x < pixel.m->cols && y < pixel.m->rows)
    {
        image.at<uchar>(y, x) = *pixel;
    }
}

cv::Mat rotate(const cv::Mat& original, double angle)
{
    cv::Mat rotated = cv::Mat::zeros(original.rows, original.cols, CV_8UC1); //почему не нужно cv:: перед типом??
        std::cout << angle << " " << sin(angle) << std::endl;

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
        std::cerr << "change_levels: " << e.what() << std::endl;
        return 1;
    }
}