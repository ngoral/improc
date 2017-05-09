#include <iostream>
#include <vector>
#include <string>

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

template <class T>
std::ostream& operator<<(std::ostream &os, const Matrix<T> &matrix) {
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

int main(void)
{
    Matrix<int> ones(3, 3, std::vector<int> (9, 1));
    Matrix<int> threes(3, 3, {3, 3, 3, 3, 3, 3, 3, 3, 3});

    std::cout << threes;
    return 0;
}