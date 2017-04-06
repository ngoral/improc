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
    return abs(angle) == 45 || abs(angle) == 90;
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

int main(int argc, char** argv)
{
    try
    {
        int angle = getAngle(argc, argv);
        std::string imageName = getImageName(argc, argv);
        std::cout << angle << std::endl;
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "change_levels: " << e.what() << std::endl;
        return 1;
    }
}