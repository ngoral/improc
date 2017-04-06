#include <iostream>
#include <stdexcept>
#include <string>
#include "improc.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

static const unsigned STD_LEVELS_NUMBER = 256;

std::string getImageName(int argc, char** argv)
{
    return (argc > 2) ? argv[2] : "no_signal.png";
}

bool isPowerOfTwo(unsigned number)
{
    return (number & (number - 1)) == 0;
}

bool LevelValid(unsigned value)
{
    return value >= 2 && value <= 256 && isPowerOfTwo(value);
}

unsigned short levelsNumber(int argc, char** argv)
{
    if (argc > 1)
    {
        if (LevelValid(std::stoi(argv[1])))
            return std::stoi(argv[1]);
        else
            throw std::runtime_error("Wrong intensity levels number `" + std::string(argv[1]) + "'");
    }
    else
        throw std::runtime_error("Could not find intensity levels number. Usage: ./change_levels levels_number [image_name] ");
}

cv::Mat changeLevels(const cv::Mat& original, unsigned short int levels)
{
    cv::Mat newImage = original.clone();
    unsigned short int coefficient = STD_LEVELS_NUMBER / levels; //always power of 2

    for(auto pixel = newImage.begin<uchar>(), end = newImage.end<uchar>(); pixel != end; ++pixel)
        *pixel = (*pixel / coefficient) * coefficient;

    return newImage;
}

int main(int argc, char** argv)
{
    try {
        unsigned short levels = levelsNumber(argc, argv);
        std::string imageName = getImageName(argc, argv);
        cv::Mat image = readImage(imageName);
        cv::Mat newImage = changeLevels(image, levels);
        cv::imwrite("changed" + filenameExtension(imageName), newImage);
        showImage(newImage);
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "change_levels: " << e.what() << std::endl;
        return 1;
    }
}