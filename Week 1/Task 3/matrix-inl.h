#include <iostream>
#include <array>
#include <string>
#include <stdexcept>
#include <algorithm>

#include <opencv2/core.hpp>

#include "matrix.h"

template <class T, size_t H, size_t W>
inline Matrix<T, H, W>::Matrix(std::array<std::array<T, W>, H> matrix):
    matrix_(matrix)
{}

template <class T, size_t H, size_t W>
inline Matrix<T, H, W>::Matrix(const T matrix[H][W])
{
    for (size_t i = 0; i != H; ++i) {
        for (size_t j = 0; j != W; ++j) {
            matrix_[i][j] = matrix[i][j];
        }
    }
}

template <class T, size_t H, size_t W>
inline Matrix<T, H, W>::Matrix(std::initializer_list<std::initializer_list<T>> matrix)
{
    std::copy(matrix.begin(), matrix.end(), matrix_);
}

template <class T, size_t H, size_t W>
inline Matrix<T, H, W>::Matrix(const Matrix<T, H, W>& matrix):
    matrix_(matrix.elements())
{}

template <class T, size_t H, size_t W>
inline Matrix<T, H, W>::Matrix(const cv::Point point):
    matrix_({static_cast<T>(point.x), static_cast<T>(point.y)})
{}


// ===========================
// == operators overloading ==
// ===========================

template <class T, size_t H, size_t W>
inline std::ostream& operator<<(std::ostream &os, const Matrix<T, H, W> &matrix)
{
    os << "[\n ";
    for (int i = 0; i != H; ++i) {
        for (int j = 0; j != W; ++j) {
            os << std::to_string(matrix.elements()[i][j]);
            if (j != W - 1) {
                os << "  ";
            }
        }
        os << "\n";
        if (i != H - 1) {
            os << " ";
        }
    }

    os << "]\n";
    return os;
}

template <class T, size_t H, size_t W>
inline Matrix<T, H, W> operator+(const Matrix<T, H, W> &matrix1, const Matrix<T, H, W> &matrix2)
{
    if (matrix1.width() != matrix2.width() || matrix1.height() != matrix2.height()) {
        throw std::runtime_error("Matrices dimensions mismatch");
    }

    T sum[H][W];
    std::transform (
        matrix1.elements().begin(), matrix1.elements().end(),
        matrix2.elements().begin(), sum,
        std::plus<T>()
    );

    return Matrix<T, H, W> (sum);
}

template <class T, size_t H, size_t W, size_t W2>
inline Matrix<T, H, W2> operator*(const Matrix<T, H, W> &matrix1, const Matrix<T, W, W2> &matrix2)
{
    if (matrix1.width() != matrix2.height()) {
        throw std::runtime_error("Matrices dimensions mismatch");
    }

    std::array<std::array<T, W2>, H> product;
    for (int i = 0; i != matrix1.height(); ++i) {
        for (int j = 0; j != matrix2.width(); ++j) {
            T sum = 0;
            for (int k = 0; k != matrix2.height(); ++k) {
                sum += matrix1.elements()[i][k] * matrix2.elements()[k][j];
            }
            product[i][j] = sum;
        }
    }

    return Matrix<T, H, W2> (product);
}

// int main(void)
// {
//     int o[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
//     int t[3][3] = {3, 0, 0, 0, 3, 0, 0, 0, 3};
//     Matrix<int, 3, 3> ones(o);
//     // Matrix<int> threes(3, 3, {3, 3, 3, 3, 3, 3, 3, 3, 3});
//     Matrix<int, 3, 3> threes(t);

//     std::cout << ones;
//     std::cout << threes;
//     std::cout << threes * ones;
//     return 0;
// }