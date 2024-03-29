#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "Введите количество элементов массива: ";
    cin >> n;

    int arr[n];

    cout << "Введите значения элементов массива:" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << "Элемент " << i + 1 << ": ";
        cin >> arr[i];
    }

    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        sum += arr[i];
    }

    cout << "Сумма элементов массива: " << sum << endl;

    return 0;
}
