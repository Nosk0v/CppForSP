#include <iostream>
#include <vector>
#include <random>

using namespace std;

vector<vector<int> > generateRandomMatrix(int rows, int cols) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    vector<vector<int> > matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dis(gen);
        }
    }

    return matrix;
}

void printMatrix(const vector<vector<int> >& matrix) {
    for (const auto& row : matrix) {
        for (int elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

int main() {
    int rows, cols;
    cout << "Введите количество строк и столбцов матрицы: ";
    cin >> rows >> cols;

    vector<vector<int> > randomMatrix = generateRandomMatrix(rows, cols);

    cout << "Сгенерированная матрица:" << endl;
    printMatrix(randomMatrix);

    return 0;
}
