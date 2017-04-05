#include <iostream>
#include <stdexcept>
#include <string>
#include "improc.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

std::string getImageName(int argc, char** argv)
{
    return (argc > 1) ? argv[1] : "no_signal.png";
}

int blurPixel(cv::MatConstIterator_<uchar> pixel)
{
    unsigned int neighbourAmount = 0, sum = 0;
    int x = pixel.pos().x, y = pixel.pos().y;
    int width = pixel.m->cols, height = pixel.m->rows;

    for (int dx = -1; dx != 2; ++dx) {
        for (int dy = -1; dy != 2; ++dy) {
            if (
                x+dx >= 0 && x+dx < width
                && y+dy >= 0 && y+dy < height
            ){
                sum += pixel[dy*width + dx];
                ++neighbourAmount;
            }
        }
    }
    return sum / neighbourAmount;
}

cv::Mat blurImage(const cv::Mat& original)
{
    cv::Mat blurred = original.clone();
    cv::MatIterator_<uchar> newPixel = blurred.begin<uchar>();

    for (
        cv::MatConstIterator_<uchar> origPixel = original.begin<uchar>(), end = original.end<uchar>();
        origPixel != end;
        ++newPixel, ++origPixel
    ){
        *newPixel = blurPixel(origPixel);
    }

    return blurred;
}

int main(int argc, char** argv)
{
    try {
        std::string imageName = getImageName(argc, argv);
        cv::Mat blurred_image = readImage(imageName);
        showImage(blurImage(blurred_image));
        cv::imwrite("blurred" + filenameExtension(imageName), blurred_image);
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "blur-image: " << e.what() << std::endl;
        return 1;
    }
}