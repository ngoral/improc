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
        std::cout <<  "Could not open or find the image" << std::endl;
        exit(-1);
    }
    return image;
}

void showImage(const cv::Mat& image)
{
    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE); //Create a window for display.
    cv::imshow("Display window", image);                //Show our image inside it.
    cv::waitKey(0); //Wait for a keystroke in the window
}

void blurPixel(cv::MatIterator_<uchar> pixel)
{
    unsigned int neighbourAmount = 0, sum = 0;
    int x = pixel.pos().x, y = pixel.pos().y;
    int width = pixel.m->cols, height = pixel.m->rows;

    if (y > 0)
    { 
        sum += pixel[-width]; //upper pix
        neighbourAmount++;
    }
    if (y < height - 1)
    {
        sum += pixel[width]; //bottom pix
        neighbourAmount++;
    }
    if (x > 0)
    {
        sum += pixel[-1]; //left pix
        neighbourAmount++;
    }
    if (x < width - 1)
    {
        sum += pixel[1]; //right pix
        neighbourAmount++;
    }

    if (x > 0 && y > 0)
    { 
        sum += pixel[-width - 1]; //upper-left pix
        neighbourAmount++;
    }
    if (x > 0 && y < height - 1)
    { 
        sum += pixel[width - 1]; //bottom-left pix
        neighbourAmount++;
    }
    if (x < width - 1 && y > 0)
    { 
        sum += pixel[-width + 1]; //upper-right pix
        neighbourAmount++;
    }
    if (x < width - 1 && y < height - 1)
    { 
        sum += pixel[width + 1]; //bottom-right pix
        neighbourAmount++;
    }

    *pixel = (*pixel + sum) / (neighbourAmount + 1);
}

cv::Mat blurImage(const cv::Mat& original)
{
    cv::Mat blurred = original.clone();
    // int nRows = blurred.rows;
    // int nCols = blurred.cols;


    for (cv::MatIterator_<uchar> pixel = blurred.begin<uchar>(), end = blurred.end<uchar>(); pixel != end; ++pixel)
    {
        blurPixel(pixel);
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