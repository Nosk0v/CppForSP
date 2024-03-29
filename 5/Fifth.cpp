#include <iostream>

using namespace std;

int main()
{
    int rows, cols;
    cout << "Введите количество строк в массиве: ";
    cin >> rows;
    cout << "Введите количество столбцов в массиве: ";
    cin >> cols;

    int arr[rows][cols];

    cout << "Введите значения элементов массива:" << endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cin >> arr[i][j];
        }
    }

    int sum = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            sum += arr[i][j];
        }
    }

    cout << "Сумма элементов массива: " << sum << endl;

    return 0;
}
