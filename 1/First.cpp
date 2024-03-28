#include <iostream>
#include <cmath>

using namespace std;

double perimeterOfSquare(double area)
{
    return 4 * sqrt(area);
}

double perimeterOfRightTriangle(double a, double b)
{
    return a + b + sqrt(a * a + b * b);
}

double sumOfGeometricProgression(double firstTerm, double ratio, int numOfTerms)
{
    return firstTerm * (1 - pow(ratio, numOfTerms)) / (1 - ratio);
}

int main()
{
    int choice;
    double a, b, firstTerm, ratio;
    int numOfTerms;

    cout << "Выберите действие:" << endl;
    cout << "1. Вычислить периметр квадрата по площади" << endl;
    cout << "2. Вычислить периметр прямоугольного треугольника" << endl;
    cout << "3. Вычислить периметр квадрата по площади" << endl;
    cout << "4. Вычислить сумму геометрической прогрессии" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Введите площадь квадрата: ";
        cin >> a;
        cout << "Периметр квадрата: " << perimeterOfSquare(a) << endl;
        break;
    case 2:
        cout << "Введите длину первого катета: ";
        cin >> a;
        cout << "Введите длину второго катета: ";
        cin >> b;
        cout << "Периметр прямоугольного треугольника: " << perimeterOfRightTriangle(a, b) << endl;
        break;
    case 3:
        cout << "Введите площадь квадрата: ";
        cin >> a;
        cout << "Периметр квадрата: " << perimeterOfSquare(a) << endl;
        break;
    case 4:
        cout << "Введите первый член геометрической прогрессии: ";
        cin >> firstTerm;
        cout << "Введите знаменатель геометрической прогрессии: ";
        cin >> ratio;
        cout << "Введите количество членов геометрической прогрессии: ";
        cin >> numOfTerms;
        cout << "Сумма геометрической прогрессии: " << sumOfGeometricProgression(firstTerm, ratio, numOfTerms) << endl;
        break;
    default:
        cout << "Неверный выбор!" << endl;
    }

    return 0;
}
