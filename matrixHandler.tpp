#include "matrixHandler.h"


template <typename T>

MatrixHandler<T>::MatrixHandler(){

}

template <typename T>

MatrixHandler<T>::~MatrixHandler(){

}

template <typename T>

void MatrixHandler<T>::printList(const std::vector<Matrix<T>>& list) const{
    for (const auto& item : list){
        item.printMatrix();
        std::cout << std::endl;
    }
}

template <typename T>

Matrix<T> MatrixHandler<T>::SumMatrixList(const std::vector<Matrix<T>>& list) const{
    Matrix<T> result(list[0].size(), list[0][0].size());

    for (const auto& item : list){
        result = result + item;
    }

    return result;
}

template <typename T>

Matrix<T> MatrixHandler<T>::MultMatrixList(const std::vector<Matrix<T>>& list) const{
    std::vector<std::vector<T>> newVector(list[0][0].size());

    for (size_t i = 0; i < newVector.size(); ++i){
        newVector[i].resize(list[0].size(), 1);
    }

    Matrix<T> result(newVector);

    for (const auto& item : list){
        result = result * item;
    }

    return result;
}

template <typename T>

std::vector<Matrix<T>> MatrixHandler<T>::FilterMatrixWithEmptyRowOrColumn(const std::vector<Matrix<T>>& list) const{

    std::vector<Matrix<T>> result;

    // Check for rows
    bool foundRow = false;
    bool foundCol = false;

    for (const auto& matrix : list){
        for (size_t i = 0; i < matrix.size(); ++i){
            for (size_t j = 0; j < matrix[i].size(); ++j){
                if (matrix[i][j] != 0){
                    break;
                }

                if (j == matrix[i].size() - 1){
                    foundRow = true;
                }
            }
        }

        for (size_t i = 0; i < matrix[0].size(); ++i) {
            for (size_t j = 0; j < matrix.size(); ++j) {
                if (matrix[j][i] != 0) {
                    break;
                }

                if (j == matrix.size() - 1){
                    foundCol = true;
                }
            }
        }

        if (foundRow || foundCol){
            result.push_back(matrix);
            foundRow = false;
            foundCol = false;
        }
    }

    return result;
}

template <typename T>

bool MatrixHandler<T>::isContinuousPath(const Matrix<T>& matrix) const{
    std::set<std::pair<size_t, size_t>> prevCoords;
    bool result = false;

    for (size_t i = 0; i < matrix[0].size(); ++i){
        if (matrix[0][i] == 0){
            result = pathFinderBottom(i, 0, matrix, prevCoords);
        }
        
        if (result){
            return true;
        }
    }

    return false; 
}

template <typename T>

bool MatrixHandler<T>::isPathToExit(const Matrix<T> matrix, size_t row, size_t col) const{
    std::set<std::pair<size_t, size_t>> prevCoords;
    std::vector<std::pair<size_t, size_t>> path;
    return pathFinderWall(row, col, matrix, prevCoords, path, path);
}

template <typename T>

bool MatrixHandler<T>::pathFinderWall(size_t x, size_t y, const Matrix<T>& matrix, std::set<std::pair<size_t, size_t>> prevCoords, std::vector<std::pair<size_t, size_t>>& outputPath, std::vector<std::pair<size_t, size_t>> path) const{
    // Base case: If we reach the walls, return true
    if (y == matrix.size() - 1 || y == 0 || x == 0 || x == matrix[0].size() - 1) {
        outputPath = path;
        outputPath.push_back({x, y});
        return true;
    }

    // Mark the current position as visited
    prevCoords.insert({x, y});
    path.push_back({x, y});

    // Move down
    if (y + 1 < matrix.size() && matrix[y + 1][x] == 0 && prevCoords.find({x, y + 1}) == prevCoords.end()) {
        if (pathFinderWall(x, y + 1, matrix, prevCoords, outputPath, path)) {
            return true;
        }
    }

    // Move up
    if (y > 0 && matrix[y - 1][x] == 0 && prevCoords.find({x, y - 1}) == prevCoords.end()) {
        if (pathFinderWall(x, y - 1, matrix, prevCoords, outputPath, path)) {
            return true;
        }
    }

    // Move left
    if (x > 0 && matrix[y][x - 1] == 0 && prevCoords.find({x - 1, y}) == prevCoords.end()) {
        if (pathFinderWall(x - 1, y, matrix, prevCoords, outputPath, path)) {
            return true;
        }
    }

    // Move right
    if (x + 1 < matrix[0].size() && matrix[y][x + 1] == 0 && prevCoords.find({x + 1, y}) == prevCoords.end()) {
        if (pathFinderWall(x + 1, y, matrix, prevCoords, outputPath, path)) {
            return true;
        }
    }

    path.clear();
    return false;
}

template <typename T>

std::vector<std::pair<size_t, size_t>> MatrixHandler<T>::PathToExit(const Matrix<T>& matrix, size_t row, size_t col) const{
    std::set<std::pair<size_t, size_t>> prevCoords;
    std::vector<std::pair<size_t, size_t>> path;
    pathFinderWall(row, col, matrix, prevCoords, path, path);
    return path;
}

template <typename T>

bool MatrixHandler<T>::pathFinderBottom(size_t x, size_t y, const Matrix<T>& matrix, std::set<std::pair<size_t, size_t>> prevCoords) const {
    // Base case: If we reach the bottom row, return true
    if (y == matrix.size() - 1) {
        return true;
    }

    // Mark the current position as visited
    prevCoords.insert({x, y});

    // Move down
    if (y + 1 < matrix.size() && matrix[y + 1][x] == 0 && prevCoords.find({x, y + 1}) == prevCoords.end()) {
        if (pathFinderBottom(x, y + 1, matrix, prevCoords)) {
            return true;
        }
    }

    // Move up
    if (y > 0 && matrix[y - 1][x] == 0 && prevCoords.find({x, y - 1}) == prevCoords.end()) {
        if (pathFinderBottom(x, y - 1, matrix, prevCoords)) {
            return true;
        }
    }

    // Move left
    if (x > 0 && matrix[y][x - 1] == 0 && prevCoords.find({x - 1, y}) == prevCoords.end()) {
        if (pathFinderBottom(x - 1, y, matrix, prevCoords)) {
            return true;
        }
    }

    // Move right
    if (x + 1 < matrix[0].size() && matrix[y][x + 1] == 0 && prevCoords.find({x + 1, y}) == prevCoords.end()) {
        if (pathFinderBottom(x + 1, y, matrix, prevCoords)) {
            return true;
        }
    }

    // If no path is found, return false
    return false;
}