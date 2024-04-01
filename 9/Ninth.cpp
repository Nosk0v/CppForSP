#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

vector<vector<int> > multiplyMatrices(const vector<vector<int> >& matrix1, const vector<vector<int> >& matrix2) {
    if (matrix1[0].size() != matrix2.size()) {
        throw invalid_argument("Number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    }

    vector<vector<int> > result(matrix1.size(), vector<int>(matrix2[0].size(), 0));

    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix2[0].size(); ++j) {
            for (size_t k = 0; k < matrix2.size(); ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
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
    vector<vector<int> > matrix1;
    matrix1.push_back(vector<int>());
    matrix1.back().push_back(1);
    matrix1.back().push_back(2);
    matrix1.back().push_back(3);

    matrix1.push_back(vector<int>());
    matrix1.back().push_back(4);
    matrix1.back().push_back(5);
    matrix1.back().push_back(6);

    vector<vector<int> > matrix2;
    matrix2.push_back(vector<int>());
    matrix2.back().push_back(7);
    matrix2.back().push_back(8);

    matrix2.push_back(vector<int>());
    matrix2.back().push_back(9);
    matrix2.back().push_back(10);

    matrix2.push_back(vector<int>());
    matrix2.back().push_back(11);
    matrix2.back().push_back(12);

    try {
        vector<vector<int> > result = multiplyMatrices(matrix1, matrix2);
        printMatrix(result);
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
