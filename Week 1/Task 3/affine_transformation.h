#pragma once
#include <opencv2/core.hpp>

#include "matrix.h"

class AffineTransformation {
public:
    static const int HEIGHT = 2;
    static const int WIDTH = 2;
    inline AffineTransformation (Matrix<double, HEIGHT, WIDTH> matrix);
    // AffineTransformation (cv::Point delta);
    inline AffineTransformation (double angle);

    // cv::Mat apply(const cv::Mat& image) const;
    inline cv::Point apply(const cv::Point& point) const;

private:
    Matrix<double, HEIGHT, WIDTH> matrix_;
};

#include "affine_transformation-inl.h"