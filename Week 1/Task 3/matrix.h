#pragma once

#include <vector>
template <class T> class Matrix {
public:
    Matrix(int height, int width, std::vector<T> matrix);
    Matrix(int height, int width, T matrix[]);

    std::vector<T> matrix() const;
    int height() const;
    int width() const;

private:
    int width_, height_;
    std::vector<T> matrix_;
};

template <class T>
std::ostream& operator<<(std::ostream &os, const Matrix<T> &matrix);