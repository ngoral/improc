#include <vector>
#include <cmath>

#include "affine_transformation.h"
#include "matrix.h"

inline AffineTransformation::AffineTransformation (Matrix<double, AffineTransformation::HEIGHT, AffineTransformation::WIDTH> matrix):
    matrix_(matrix)
{}

inline AffineTransformation::AffineTransformation (double angle)
{
    matrix_ = Matrix<double, AffineTransformation::HEIGHT, AffineTransformation::WIDTH> (
        { cos(angle), -sin(angle), 
          sin(angle), cos(angle)}
    );
}

inline cv::Point AffineTransformation::apply(const cv::Point& point) const
{
    Matrix<double, AffineTransformation::HEIGHT, AffineTransformation::WIDTH> object(point);
    Matrix<double, AffineTransformation::HEIGHT, AffineTransformation::WIDTH> result = matrix_ * object;
    return cv::Point(result.elements()[0][0], result.elements()[1][0]);
}


// int main(void) {
//     AffineTransformation at(M_PI / 2);
//     return 0;
// }