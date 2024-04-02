#include <iostream>

// Function declarations
void add(int, int);
void subtract(int, int);
void multiply(int, int);

int main()
{
    int a = 10;
    int b = 5;
    void (*operations[3])(int, int) = {add, subtract, multiply};
       
    // Get the length of the array
    unsigned length = sizeof(operations) / sizeof(operations[0]);
       
    for(unsigned i = 0; i < length; i++)
    {
        operations[i](a, b);    // Call the function via pointer
    }

    return 0;
}

// Function definitions
void add(int x, int y)
{
    std::cout << "x + y = " << x + y << std::endl;
}

void subtract(int x, int y)
{
    std::cout << "x - y = " << x - y << std::endl;
}

void multiply(int x, int y)
{
    std::cout << "x * y = " << x * y << std::endl;
}