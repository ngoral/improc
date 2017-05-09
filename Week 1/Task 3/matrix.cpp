#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

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

template <class T>
const std::vector<T>& Matrix<T>::matrix() const
{
    return matrix_;
}

template <class T>
int Matrix<T>::height() const
{
    return height_;
}

template <class T>
int Matrix<T>::width() const
{
    return width_;
}

// ===========================
// == operators overloading ==
// ===========================

template <class T>
std::ostream& operator<<(std::ostream &os, const Matrix<T> &matrix)
{
    std::string printableString = "[\n ";
    for (int i = 0; i != matrix.height(); ++i) {
        for (int j = 0; j != matrix.width(); ++j) {
            printableString += std::to_string(matrix.matrix().at(matrix.width() * i + j));
            if (j != matrix.width() - 1) {
                printableString += "  ";
            }
        }
        printableString += "\n";
        if (i != matrix.height() - 1) {
            printableString += " ";
        }
    }

    printableString += "]\n";
    return os << printableString;
}

template <class T>
Matrix<T> operator+(const Matrix<T> &matrix1, const Matrix<T> &matrix2)
{
    if ((matrix1.width() == matrix2.width()) && (matrix1.height() == matrix2.height())) {
        std::vector<T> sumVector;
        for (
            auto elem1 = matrix1.matrix().begin(), elem2 = matrix2.matrix().begin();
            elem1 != matrix1.matrix().end();
            ++elem1, ++elem2
        ) {
            sumVector.push_back(*elem1 + *elem2);
        }

        return Matrix<T> (matrix1.height(), matrix1.width(), sumVector);
    }
    else
    {
        throw std::runtime_error("Matrix sizes should be equal");
    }
}

int main(void)
{
    Matrix<int> ones(3, 3, std::vector<int> (9, 1));
    Matrix<int> threes(3, 3, {3, 3, 3, 3, 3, 3, 3, 3, 3});

    std::cout << ones;
    std::cout << threes;
    std::cout << threes + ones;
    return 0;
}