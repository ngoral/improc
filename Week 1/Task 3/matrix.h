#pragma once

#include <vector>
template <class T> class Matrix {
public:
    Matrix(int height, int width, std::vector<T> matrix);
    Matrix(int height, int width, T matrix[]);
    Matrix(const Matrix<T>& matrix);

    //getters
    const std::vector<T>& matrix() const { return matrix_; }
    int height() const { return height_; }
    int width() const { return width_; }

    //setters
    void setElements (const std::vector<T>& elements) { matrix_ = elements; }

private:
    int width_, height_;
    std::vector<T> matrix_;
};

template <class T>
std::ostream& operator<<(std::ostream &os, const Matrix<T> &matrix);
template <class T>
Matrix<T> operator+(const Matrix<T> &matrix1, const Matrix<T> &matrix2);
template <class T>
Matrix<T> operator*(const Matrix<T> &matrix1, const Matrix<T> &matrix2);