#include <iostream>
#include <stdexcept>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

std::string getImageName(int argc, char** argv)
{
    return (argc > 2) ? argv[1] : "no_signal.png";
}

bool isRightLevelValue(char* value)
{
    int v = std::stoi(value);
    return v >= 2 && v <= 256 && ((v) & (v-1)) == 0;
}

int levelsNumber(int argc, char** argv)
{
    if (argc > 1)
    {
        if (isRightLevelValue(argv[1]))
            return std::stoi(argv[1]);
        else
            throw std::runtime_error("Wrong intensity levels number `" + std::string(argv[1]) + "'");
    }
    else
        throw std::runtime_error("Could not find intensity levels number. Usage: ./change_levels levels_number [image_name] ");
}

cv::Mat readImage(const std::string& imageName)
{
    cv::Mat image = cv::imread(imageName, cv::IMREAD_GRAYSCALE); //Read the file (grayscale image)
    if (image.empty())                                           //Check for invalid input
        throw std::runtime_error("Could not open or find the image `" + imageName + "'");
    return image;
}

int main(int argc, char** argv)
{
    try {
        int levels = levelsNumber(argc, argv);
        std::string imageName = getImageName(argc, argv);
        std::cout << levels << ";" << imageName << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "change_levels: " << e.what() << std::endl;
        return 1;
    }
}