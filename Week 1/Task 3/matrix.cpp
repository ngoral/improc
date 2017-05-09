#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "matrix.h"


template <class T>
Matrix<T>::Matrix(int height, int width, std::vector<T> matrix):
    height_(height),
    width_(width),
    matrix_(matrix)
{}

template <class T>
Matrix<T>::Matrix(int height, int width, T matrix[]):
    height_(height),
    width_(width),
    matrix_(matrix.begin(), matrix.end())
{}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& matrix):
    height_(matrix.height()),
    width_(matrix.width()),
    matrix_(matrix.matrix())
{}

// ===========================
// == operators overloading ==
// ===========================

template <class T>
std::ostream& operator<<(std::ostream &os, const Matrix<T> &matrix)
{
    os << "[\n ";
    for (int i = 0; i != matrix.height(); ++i) {
        for (int j = 0; j != matrix.width(); ++j) {
            os << std::to_string(matrix.matrix().at(matrix.width() * i + j));
            if (j != matrix.width() - 1) {
                os << "  ";
            }
        }
        os << "\n";
        if (i != matrix.height() - 1) {
            os << " ";
        }
    }

    os << "]\n";
    return os;
}

template <class T>
Matrix<T> operator+(const Matrix<T> &matrix1, const Matrix<T> &matrix2)
{
    if (matrix1.width() != matrix2.width() || matrix1.height() != matrix2.height()) {
        throw std::runtime_error("Matrix sizes should be equal");
    }

    std::vector<T> sumVector;
    std::transform (
        matrix1.matrix().begin(), matrix1.matrix().end(),
        matrix2.matrix().begin(), std::back_inserter(sumVector),
        std::plus<T>()
    );

    return Matrix<T> (matrix1.height(), matrix1.width(), sumVector);
}

template <class T>
Matrix<T> operator*(const Matrix<T> &matrix1, const Matrix<T> &matrix2)
{
    if (matrix1.width() != matrix2.height()) {
        throw std::runtime_error("Bad matrix sizes");
    }

    std::vector<T> prodVector;
    for (
        auto line1 = matrix1.matrix().begin(); line1 < matrix1.matrix().end(); line1 += matrix1.width()) {

        for (auto col2 = matrix2.matrix().begin(); col2 != matrix2.matrix().begin() + matrix2.height(); ++col2) {
            T sum = 0;
            for (
                auto elem1 = line1, elem2 = col2;
                elem1 != line1 + matrix1.width();
                ++elem1, elem2 += matrix2.width()) {
                sum += *elem1 * *elem2;
            }
            prodVector.push_back(sum);
        }
    }

    return Matrix<T> (matrix1.height(), matrix2.width(), prodVector);
}

int main(void)
{
    Matrix<int> ones(3, 3, std::vector<int> (9, 1));
    // Matrix<int> threes(3, 3, {3, 3, 3, 3, 3, 3, 3, 3, 3});
    Matrix<int> threes(3, 3, {3, 0, 0, 0, 3, 0, 0, 0, 3});

    std::cout << ones;
    std::cout << threes;
    std::cout << threes * ones;
    return 0;
}