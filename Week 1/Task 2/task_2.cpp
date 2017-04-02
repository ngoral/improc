#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

cv::String getImageName(int argc, char** argv)
{
    cv::String imageName("no_signal.png"); //by default
    if (argc > 1)
    {
        imageName = argv[1];
    }
    return imageName;
}

cv::Mat readImage(const cv::String& imageName)
{
    cv::Mat image;
    image = cv::imread(imageName, cv::IMREAD_GRAYSCALE); //Read the file (grayscale image)
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

int main(int argc, char** argv)
{
    cv::String imageName = getImageName(argc, argv);
    cv::Mat image = readImage(imageName);
    showImage(blurImage(image));
    return 0;
}