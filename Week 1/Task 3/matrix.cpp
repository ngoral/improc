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
    matrix_(matrix.elements())
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
            os << std::to_string(matrix.elements().at(matrix.width() * i + j));
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
        throw std::runtime_error("Matrices dimensions mismatch");
    }

    std::vector<T> sumVector;
    std::transform (
        matrix1.elements().begin(), matrix1.elements().end(),
        matrix2.elements().begin(), std::back_inserter(sumVector),
        std::plus<T>()
    );

    return Matrix<T> (matrix1.height(), matrix1.width(), sumVector);
}

template <class T>
Matrix<T> operator*(const Matrix<T> &matrix1, const Matrix<T> &matrix2)
{
    if (matrix1.width() != matrix2.height()) {
        throw std::runtime_error("Matrices dimensions mismatch");
    }

    std::vector<T> prodVector;
    // for (auto line1 = matrix1.elements().begin(); line1 < matrix1.elements().end(); line1 += matrix1.width()) {
    //     for (auto col2 = matrix2.elements().begin(); col2 != matrix2.elements().begin() + matrix2.height(); ++col2) {
    //         T sum = 0;
    //         for (
    //             auto elem1 = line1, elem2 = col2;
    //             elem1 != line1 + matrix1.width();
    //             ++elem1, elem2 += matrix2.width()
    //         ) {
    //             sum += *elem1 * *elem2;
    //         }
    //         prodVector.push_back(sum);
    //     }
    // }

    for (int i = 0; i != matrix1.height(); ++i) {
        for (int j = 0; j != matrix2.width(); ++j) {
            T sum = 0;
            for (int k = 0; k != matrix2.height(); ++k) {
                sum += matrix1.elements().at( matrix1.width() * i + k) * matrix2.elements().at(matrix2.width() * k + j);
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