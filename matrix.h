#ifndef MATRIX_h
#define MATRIX_h

#include <iostream>
#include <vector>
#include <initializer_list>

template <typename T>

class Matrix{

    public:
        Matrix();
        Matrix(size_t rows, size_t cols);
        Matrix(size_t rows, size_t cols, int min, int max);
        Matrix(size_t rows, size_t cols, T value);
        Matrix(std::vector<std::vector<T>>& newMatrix);
        Matrix(std::initializer_list<std::initializer_list<T>> initList);
        ~Matrix();

        std::vector<T>& operator[](size_t value);
        const std::vector<T>& operator[](size_t value) const;
        size_t getCols() const;
        size_t getRows() const;
        void printMatrix() const;
        size_t size() const;

        Matrix<T> operator+(const Matrix<T>& otherMatrix) const;
        Matrix<T> operator+(const std::vector<std::vector<T>>& otherMatrix) const;

        Matrix<T> operator*(T value) const;
        Matrix<T> operator*(const Matrix<T>& otherMatrix) const;

        Matrix<T> transpose() const;

    private:
        std::vector<std::vector<T>> matrix;
        size_t cols_;
        size_t rows_;
};

#include "matrix.tpp"

#endif