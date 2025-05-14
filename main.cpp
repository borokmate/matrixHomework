#include "matrix.h"
#include "matrixHandler.h"
#include <vector>

void printBigLine();

int main(){

    // The matrices I will be using

    MatrixHandler<int> matrixHandler;

    Matrix<int> mazeMatrix({
        {1, 0, 5, 5, 7},
        {2, 0, 6, 2, 3},
        {2, 0, 0, 9, 1},
        {1, 0, 2, 2, 3},
        {0, 1, 4, 5, 7}
    });

    Matrix<int> continousMatrix({
        {1, 0, 5, 5, 7},
        {2, 0, 6, 2, 3},
        {2, 0, 0, 9, 1},
        {1, 0, 0, 0, 3},
        {0, 1, 4, 0, 7}
    });

    Matrix<int> matrix1({
        {3, 1},
        {2, 1},
        {1, 0}
    });

    Matrix<int> matrix2({
        {1, 2, 3},
        {4, 5, 6}
    });

    Matrix<int> matrix3({
        {6, 5, 4},
        {3, 2, 1}
    });

    Matrix<int> emptyColMatrix({
        {6, 5, 0},
        {3, 2, 0}
    });

    Matrix<int> emptyRowMatrix({
        {0, 0, 0},
        {3, 2, 2}
    });

    std::vector<Matrix<int>> listWithEmpty;

    Matrix<int> outputMatrix;

    // A) adding two matrices together

    std::cout << "A)\n" << std::endl;
    outputMatrix = matrix2 + matrix3;
    outputMatrix.printMatrix();

    printBigLine();

    // B) scalar multiply

    std::cout << "B)\n" << std::endl;
    outputMatrix = matrix2 * 3;
    outputMatrix.printMatrix();

    printBigLine();

    // C) matrix with matrix multiply

    std::cout << "C)\n" << std::endl;
    outputMatrix = matrix1 * matrix2;
    outputMatrix.printMatrix();

    printBigLine();

    // D) transpose

    std::cout << "D)\n" << std::endl;
    outputMatrix = matrix2.transpose();
    matrix2.printMatrix();
    std::cout << std::endl;
    outputMatrix.printMatrix();


    // normal things done

    std::vector<Matrix<int>> matrixList;
    std::vector<Matrix<int>> additiveMatrixList;

    size_t rows = 2;
    size_t cols = 3;
    int min = 0;
    int max = 6;
    // min and max are for adding random numbers

    for (int i = 0; i < 2; ++i){
        Matrix<int> matrix(rows, cols, min, max);
        if (i % 2 == 0){
            matrix = matrix.transpose(); // when multiplying, one's width, has to be the others height, so this is how I solved that
        }
        matrixList.push_back(matrix);
        listWithEmpty.push_back(matrix);
    }

    for (int i = 0; i < 2; ++i){
        Matrix<int> matrix(rows, cols, min, max);
        additiveMatrixList.push_back(matrix);
    }

    listWithEmpty.push_back(emptyColMatrix);
    listWithEmpty.push_back(emptyRowMatrix);

    std::vector<Matrix<int>> outputList;

    printBigLine();

    std::cout << "Second part: " << std::endl;

    // 1) adding together the list

    std::cout << "1)\n" << std::endl;
    outputMatrix = matrixHandler.SumMatrixList(additiveMatrixList);
    outputMatrix.printMatrix();
    printBigLine();

    // 2) multiplying the list

    std::cout << "2)\n" << std::endl;
    outputMatrix = matrixHandler.MultMatrixList(matrixList);
    outputMatrix.printMatrix();
    printBigLine();

    // 3) empty row or col list

    std::cout << "3)\n" << std::endl;
    matrixList = matrixHandler.FilterMatrixWithEmptyRowOrColumn(listWithEmpty);
    matrixHandler.printList(matrixList);
    printBigLine();

    // 4) isContinousPath

    std::cout << "4)\n" << std::endl;
    bool doesPathExist = false;
    doesPathExist = matrixHandler.isContinuousPath(continousMatrix);
    std::cout << doesPathExist << std::endl;
    printBigLine();

    // 5a) isPathToWall

    std::cout << "5a)\n" << std::endl;
    size_t row = 2;
    size_t col = 2;

    doesPathExist = matrixHandler.isPathToExit(mazeMatrix, row, col);
    std::cout << doesPathExist << std::endl;
    printBigLine();

    // 5b) printPathToWall;

    std::cout << "5b)\n" << std::endl;
    std::vector<std::pair<size_t, size_t>> path = matrixHandler.PathToExit(mazeMatrix, row, col);
    int i = 1;
    for (const auto& item : path){
        std::cout << ++i << ": " << item.first << " - " << item.second << std::endl;
    }
    printBigLine();

    return 0;
}

void printBigLine(){
    std::cout << "-----------------------------------------------------------------------" << std::endl;
}