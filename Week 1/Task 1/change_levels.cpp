#include <iostream>
#include <stdexcept>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#define STD_LEVELS_NUMBER 256

std::string getImageName(int argc, char** argv)
{
    return (argc > 2) ? argv[2] : "no_signal.png";
}

bool isRightLevelValue(char* value)
{
    int v = std::stoi(value);
    return v >= 2 && v <= 256 && ((v) & (v-1)) == 0;
}

unsigned short int levelsNumber(int argc, char** argv)
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

cv::Mat changeLevels(const cv::Mat& original, unsigned short int levels)
{
    cv::Mat newImage = original.clone();
    unsigned short int koefficient = STD_LEVELS_NUMBER / levels; //always power of 2

    for(auto pixel = newImage.begin<uchar>(), end = newImage.end<uchar>(); pixel != end; ++pixel)
        *pixel = (*pixel / koefficient) * koefficient;

    return newImage;
}

int main(int argc, char** argv)
{
    try {
        unsigned short int levels = levelsNumber(argc, argv);
        std::string imageName = getImageName(argc, argv);
        cv::Mat image = readImage(imageName);
        cv::Mat newImage = changeLevels(image, levels);
        std::cout << levels << ";" << imageName << std::endl;
        cv::imwrite("changed" + filenameExtension(imageName), newImage);
        showImage(newImage);
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "change_levels: " << e.what() << std::endl;
        return 1;
    }
}