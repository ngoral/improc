#pragma once

#include <iostream>
#include <vector>

template <class T> class Matrix {
public:
    inline Matrix();
    inline Matrix(int height, int width, std::vector<T> matrix);
    inline Matrix(int height, int width, T matrix[]);
    inline Matrix(const Matrix<T>& matrix);

    //getters
    inline const std::vector<T>& elements() const { return matrix_; }
    inline int height() const { return height_; }
    inline int width() const { return width_; }

    //setters
    inline void setElements (const std::vector<T>& elements) { matrix_ = elements; }

private:
    int width_, height_;
    std::vector<T> matrix_;
};

template <class T>
inline std::ostream& operator<<(std::ostream &os, const Matrix<T> &matrix);
template <class T>
inline Matrix<T> operator+(const Matrix<T> &matrix1, const Matrix<T> &matrix2);
template <class T>
inline Matrix<T> operator*(const Matrix<T> &matrix1, const Matrix<T> &matrix2);

#include "matrix-inl.h"