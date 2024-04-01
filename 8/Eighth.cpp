#include <iostream>
#include <vector>

using namespace std;

vector<vector<int> > multiplyMatrixByScalar(const vector<vector<int> >& matrix, int scalar) {
    vector<vector<int> > result(matrix.size(), vector<int>(matrix[0].size()));

    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }

    return result;
}

void printMatrix(const vector<vector<int> >& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int> > matrix;
    vector<int> row1;
    row1.push_back(1);
    row1.push_back(2);
    row1.push_back(3);
    matrix.push_back(row1);

    vector<int> row2;
    row2.push_back(4);
    row2.push_back(5);
    row2.push_back(6);
    matrix.push_back(row2);

    vector<int> row3;
    row3.push_back(7);
    row3.push_back(8);
    row3.push_back(9);
    matrix.push_back(row3);

    int scalar = 2;

    vector<vector<int> > result = multiplyMatrixByScalar(matrix, scalar);

    printMatrix(result);

    return 0;
}
