#include "matrix.h"
#include <stdexcept>
#include <random>

template <typename T>

Matrix<T>::Matrix(size_t rows, size_t cols){
    matrix.resize(rows);

    for (auto& row : matrix){
        row.resize(cols, 0);
    }

    cols_ = cols;
    rows_ = rows;
}

template <typename T>

Matrix<T>::Matrix(){
    
}

template <typename T>

Matrix<T>::Matrix(size_t rows, size_t cols, T value){
    matrix.resize(rows);

    for (auto& row : matrix){
        row.resize(cols, value);
    }

    cols_ = cols;
    rows_ = rows;
}

template <typename T>

Matrix<T>::Matrix(size_t rows, size_t cols, int min, int max){
    matrix.resize(rows);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(min, max);

    for (auto& row : matrix) {
        row.resize(cols);
        for (auto& element : row) {
            element = dist(rng);
        }
    }

    cols_ = cols;
    rows_ = rows;
}

template <typename T>

Matrix<T>::Matrix(std::vector<std::vector<T>>& newMatrix){
    matrix = newMatrix;
}

template <typename T>

Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> initList) {
    rows_ = initList.size();
    cols_ = initList.begin()->size();
    matrix = std::vector<std::vector<T>>(rows_, std::vector<T>(cols_));

    size_t i = 0;
    for (const auto& row : initList) {
        matrix[i++] = std::vector<T>(row);
    }
}

template <typename T>

Matrix<T>::~Matrix() {
    // No explicit cleanup needed since std::vector handles its own memory
}

template <typename T>

void Matrix<T>::printMatrix() const{
    for (const auto& row : matrix){
        for (const auto& col : row){
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>

std::vector<T>& Matrix<T>::operator[](size_t value){
    if (value > matrix.size()) {
        std::cout << "You stupid" << std::endl;
    }

    return matrix[value];
}

template <typename T>
const std::vector<T>& Matrix<T>::operator[](size_t value) const {
    if (value >= matrix.size()) {
        throw std::out_of_range("Index out of range");
    }
    return matrix[value];
}

template <typename T>

size_t Matrix<T>::size() const{
    return matrix.size();
}

template <typename T>

Matrix<T> Matrix<T>::operator+(const Matrix<T>& otherMatrix) const{

    Matrix<T> tempMatrix(rows_, cols_);

    if (otherMatrix.size() != matrix.size() || otherMatrix[0].size() != matrix[0].size()){
        throw std::out_of_range("The two matrices are not the same size");
    }

    for (size_t row = 0; row < matrix.size(); ++row){
        for (size_t col = 0; col < matrix[col].size(); ++col){
            tempMatrix[row][col] = matrix[row][col] + otherMatrix[row][col];
        }
    }

    return tempMatrix;
}

template <typename T>

Matrix<T> Matrix<T>::operator+(const std::vector<std::vector<T>>& otherMatrix) const{

    Matrix<T> tempMatrix(rows_, cols_);

    for (size_t row = 0; row < matrix.size(); ++row){
        for (size_t col = 0; col < matrix[col].size(); ++col){
            tempMatrix.setValue(row, col, matrix[row][col] + otherMatrix[row][col]);
        }
    }

    return tempMatrix;
}

template <typename T>

Matrix<T> Matrix<T>::operator*(T value) const{

    Matrix<T> tempMatrix(rows_, cols_);

    for (size_t row = 0; row < matrix.size(); ++row){
        for (size_t col = 0; col < matrix[col].size(); ++col){
            tempMatrix[row][col] = value * matrix[row][col];
        }
    }

    return tempMatrix;
}

template <typename T>

Matrix<T> Matrix<T>::operator*(const Matrix<T>& otherMatrix) const{

    size_t aRows = matrix.size();
    size_t aCols = matrix[0].size();
    size_t bRows = otherMatrix.getRows();
    size_t bCols = otherMatrix[0].size();

    if (aCols != bRows) {
        throw std::out_of_range("The two matrices aren't the correct sizes");
    }

    Matrix<T> result(aRows, bCols);
    for (size_t i = 0; i < aRows; ++i) {
        for (size_t j = 0; j < bCols; ++j) {
            for (size_t k = 0; k < aCols; ++k) {
                result[i][j] += matrix[i][k] * otherMatrix[k][j];
            }
        }
    }
    return result;
}

template <typename T>

Matrix<T> Matrix<T>::transpose() const{
    Matrix<T> tempMatrix(cols_, rows_);

    for (size_t row = 0; row < rows_; ++row){
        for (size_t col = 0; col < cols_; ++col){
            tempMatrix[col][row] = matrix[row][col];
        }
    }

    return tempMatrix;
}

template <typename T>
size_t Matrix<T>::getRows() const {
    return rows_;
}