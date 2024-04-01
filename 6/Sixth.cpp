#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > addOrSubtractMatrices(const vector<vector<int> >& matrix1, const vector<vector<int> >& matrix2, bool addition) {
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        cout << "Ошибка: размерности матриц не совпадают!" << endl;
        exit(1);
    }

    vector<vector<int> > result(matrix1.size(), vector<int>(matrix1[0].size()));

    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix1[0].size(); ++j) {
            result[i][j] = addition ? matrix1[i][j] + matrix2[i][j] : matrix1[i][j] - matrix2[i][j];
        }
    }

    return result;
}

void printMatrix(const vector<vector<int> >& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int> > matrix1(3, vector<int>(3));
    matrix1[0][0] = 1;
    matrix1[0][1] = 2;
    matrix1[0][2] = 3;
    matrix1[1][0] = 4;
    matrix1[1][1] = 5;
    matrix1[1][2] = 6;
    matrix1[2][0] = 7;
    matrix1[2][1] = 8;
    matrix1[2][2] = 9;

    vector<vector<int> > matrix2(3, vector<int>(3));
    matrix2[0][0] = 9;
    matrix2[0][1] = 8;
    matrix2[0][2] = 7;
    matrix2[1][0] = 6;
    matrix2[1][1] = 5;
    matrix2[1][2] = 4;
    matrix2[2][0] = 3;
    matrix2[2][1] = 2;
    matrix2[2][2] = 1;

    cout << "Матрица 1:" << endl;
    printMatrix(matrix1);
    cout << endl;

    cout << "Матрица 2:" << endl;
    printMatrix(matrix2);
    cout << endl;

    cout << "Результат сложения матриц:" << endl;
    vector<vector<int> > resultAdd = addOrSubtractMatrices(matrix1, matrix2, true);
    printMatrix(resultAdd);
    cout << endl;

    cout << "Результат вычитания матриц:" << endl;
    vector<vector<int> > resultSub = addOrSubtractMatrices(matrix1, matrix2, false);
    printMatrix(resultSub);
    cout << endl;

    return 0;
}
