#include <iostream>

using namespace std;

unsigned long long factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i)
    {
        result *= i;
    }
    return result;
}

unsigned long long power(int base, int exponent)
{
    if (exponent == 0)
    {
        return 1;
    }
    unsigned long long result = 1;
    for (int i = 1; i <= exponent; ++i)
    {
        result *= base;
    }
    return result;
}

int main()
{
    int choice, N, M;

    cout << "Выберите действие:" << endl;
    cout << "1. Получить факториал числа N" << endl;
    cout << "2. Получить значение N в степени M" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Введите число N: ";
        cin >> N;
        cout << "Факториал числа " << N << " равен " << factorial(N) << endl;
        break;
    case 2:
        cout << "Введите число N: ";
        cin >> N;
        cout << "Введите степень M: ";
        cin >> M;
        cout << N << " в степени " << M << " равно " << power(N, M) << endl;
        break;
    default:
        cout << "Неверный выбор!" << endl;
    }

    return 0;
}
