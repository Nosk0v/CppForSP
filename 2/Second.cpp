#include <iostream>
#include <cmath>

using namespace std;

void solveQuadraticEquation(double a, double b, double c)
{
    double discriminant = b * b - 4 * a * c;
    if (discriminant > 0)
    {
        double root1 = (-b + sqrt(discriminant)) / (2 * a);
        double root2 = (-b - sqrt(discriminant)) / (2 * a);
        cout << "У уравнения есть два корня: x1 = " << root1 << ", x2 = " << root2 << endl;
    }
    else if (discriminant == 0)
    {
        double root = -b / (2 * a);
        cout << "У уравнения есть один корень: x = " << root << endl;
    }
    else
    {
        cout << "У уравнения нет действительных корней." << endl;
    }
}

void checkDivision(int M, int N)
{
    if (M % N == 0)
    {
        cout << "Частное от деления M на N: " << M / N << endl;
    }
    else
    {
        cout << "M на N нацело не делится." << endl;
    }
}
bool isTrianglePossible(double a, double b, double c)
{
    return (a + b > c && a + c > b && b + c > a);
}

bool isMultipleOfThree(int number)
{
    int sumOfDigits = 0;
    while (number > 0)
    {
        sumOfDigits += number % 10;
        number /= 10;
    }
    return sumOfDigits % 3 == 0;
}

int main()
{
    int choice;
    double a, b, c;
    int M, N;

    cout << "Выберите действие:" << endl;
    cout << "1. Решить квадратное уравнение" << endl;
    cout << "2. Проверить деление целых чисел" << endl;
    cout << "3. Проверить возможность существования треугольника" << endl;
    cout << "4. Проверить кратность трехзначного числа трём" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Введите коэффициенты a, b, c для уравнения ax^2 + bx + c = 0: ";
        cin >> a >> b >> c;
        solveQuadraticEquation(a, b, c);
        break;
    case 2:
        cout << "Введите два целых числа M и N: ";
        cin >> M >> N;
        checkDivision(M, N);
        break;
    case 3:
        cout << "Введите длины сторон треугольника a, b, c: ";
        cin >> a >> b >> c;
        if (isTrianglePossible(a, b, c))
        {
            cout << "Треугольник с такими сторонами существует." << endl;
        }
        else
        {
            cout << "Треугольник с такими сторонами не существует." << endl;
        }
        break;
    case 4:
        int number;
        cout << "Введите трехзначное число: ";
        cin >> number;
        if (isMultipleOfThree(number))
        {
            cout << "Сумма цифр числа " << number << " кратна трём." << endl;
        }
        else
        {
            cout << "Сумма цифр числа " << number << " не кратна трём." << endl;
        }
        break;
    default:
        cout << "Неверный выбор!" << endl;
    }

    return 0;
}
