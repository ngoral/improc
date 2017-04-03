#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

std::string getImageName(int argc, char** argv)
{
    return (argc > 1) ? argv[1] : "no_signal.png";
}

cv::Mat readImage(const std::string& imageName)
{
    cv::Mat image = cv::imread(imageName, cv::IMREAD_GRAYSCALE); //Read the file (grayscale image)
    if (image.empty())                      //Check for invalid input
    {
        std::cerr << "blur-image: could not open or find the image `" << imageName << "'" << std::endl;
        exit(1);
    }
    return image;
}

void showImage(const cv::Mat& image)
{
    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); //Create a window for display.
    cv::imshow("Display window", image);                //Show our image inside it.
    cv::waitKey(0); //Wait for a keystroke in the window
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

std::string filenameExtension(const std::string& filename)
{
    size_t dot = filename.rfind('.');
    size_t basename = filename.rfind('/') + 1;
    return (dot != std::string::npos && dot > basename) ? filename.substr(dot) : ".png";
}

int main(int argc, char** argv)
{
    std::string imageName = getImageName(argc, argv);
    cv::Mat blurred_image = readImage(imageName);
    showImage(blurImage(blurred_image));
    imwrite("blurred" + filenameExtension(imageName), blurred_image);
    return 0;
}