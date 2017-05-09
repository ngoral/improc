#pragma once

#include <iostream>
// #include <vector>
#include <array>

#include <opencv2/core.hpp>

template <class T, size_t H, size_t W> class Matrix {
public:
    inline Matrix() {}
    inline Matrix(std::array<std::array<T, W>, H> matrix);
    inline Matrix(const T matrix[H][W]);
    inline Matrix(std::initializer_list<std::initializer_list<T>> matrix);
    inline Matrix(const Matrix<T, H, W>& matrix);
    inline Matrix(const cv::Point point);

    //getters
    inline std::array<std::array<T, W>, H> elements() const { return matrix_; }
    inline size_t height() const { return H; }
    inline size_t width() const { return W; }

    //setters
    inline void setElements (const T elements[H][W]) { matrix_ = elements; }

private:
    std::array<std::array<T, W>, H> matrix_;
};

template <class T, size_t H, size_t W>
inline std::ostream& operator<<(std::ostream &os, const Matrix<T, H, W> &matrix);
template <class T, size_t H, size_t W>
inline Matrix<T, H, W> operator+(const Matrix<T, H, W> &matrix1, const Matrix<T, H, W> &matrix2);
template <class T, size_t H, size_t W, size_t W2>
inline Matrix<T, H, W2> operator*(const Matrix<T, H, W> &matrix1, const Matrix<T, W, W2> &matrix2);

#include "matrix-inl.h"