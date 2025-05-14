#ifndef MATRIXHANDLER_h
#define MATRIXHANDLER_h
#include "matrix.h"
#include <vector>
#include <set>
#include <string>

template <typename T>

class MatrixHandler{

    public:

        MatrixHandler();
        ~MatrixHandler();

        Matrix<T> SumMatrixList(const std::vector<Matrix<T>>& list) const;
        Matrix<T> MultMatrixList(const std::vector<Matrix<T>>& list) const;

        void printList(const std::vector<Matrix<T>>& list) const; 

        std::vector<Matrix<T>> FilterMatrixWithEmptyRowOrColumn(const std::vector<Matrix<T>>& list) const;
        bool isContinuousPath(const Matrix<T>& matrix) const;
        bool isPathToExit(const Matrix<T> matrix, size_t row, size_t col) const;
        std::vector<std::pair<size_t, size_t>> PathToExit(const Matrix<T>& matrix, size_t row, size_t col) const;

        bool pathFinderWall(size_t x, size_t y, const Matrix<T>& matrix, std::set<std::pair<size_t, size_t>> prevCoords, std::vector<std::pair<size_t, size_t>>& outputPath, std::vector<std::pair<size_t, size_t>> path) const;
        bool pathFinderBottom(size_t x, size_t y, const Matrix<T>& matrix, std::set<std::pair<size_t, size_t>> prevCoords) const;

    private:
        std::vector<Matrix<T>> matrixList;
};

#include "matrixHandler.tpp"

#endif