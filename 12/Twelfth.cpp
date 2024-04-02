#include <iostream>
#include <array>
#include <algorithm>

// Условия
bool isEven(int);
bool isPositive(int);

// Функция для определения элементов массива, которые соответствуют некоторому условию
void action(bool(*)(int), const std::array<int, 11>&);

int main()
{
    std::array<int, 11> numbers = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 };

    std::cout << "Четные числа: ";
    action(isEven, numbers);

    std::cout << "\nПоложительные числа: ";
    action(isPositive, numbers);

    return 0;
}

bool isEven(int x)
{
    return x % 2 == 0;
}

bool isPositive(int x)
{
    return x > 0;
}

void action(bool(*condition)(int), const std::array<int, 11>& numbers)
{
    for (int num : numbers)
    {
        if (condition(num))
        {
            std::cout << num << " ";
        }
    }
}
