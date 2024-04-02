#include <iostream>
#include <array>

int add(int x, int y);
int subtract(int x, int y);
int multiply(int x, int y);
int (*select(int choice))(int, int);

int main() {
    int (*action)(int, int) = select(1); // Получаем указатель на функцию
    if (action) { // Если не равно nullptr
        std::cout << action(8, 5) << std::endl;
    } else {
        std::cout << "Undefined" << std::endl;
    }
}

std::array<int(*)(int, int), 3> actions = {add, subtract, multiply};

int (*select(int choice))(int, int) {
    // Возвращаем нужную функцию в зависимости от choice
    // Возвращаем нужную функцию
    return actions.at(choice - 1);
}

int add(int x, int y) { return x + y; }
int subtract(int x, int y) { return x - y; }
int multiply(int x, int y) { return x * y; }