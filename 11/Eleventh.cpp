#include <iostream>
  
// BinaryOp представляет указатель на функцию типа int (*)(int, int)
using BinaryOp = int (*)(int, int);
 
int sum(int, int);
int subtract(int, int);
void do_operation(int, int, BinaryOp);
 
int main()
{
    BinaryOp operation = sum; // Используем явное присваивание
    std::cout << operation(8, 5) << std::endl;  // 13
    operation = subtract;
    std::cout << operation(8, 5) << std::endl;  // 3
    
    do_operation(10, 6, sum);       // 16
    do_operation(10, 6, subtract);  // 4
}
 
void do_operation(int a, int b, BinaryOp op)
{
    double result = op(a, b);
    std::cout << result << std::endl;
}
 
int sum(int x, int y) { return x + y; }
int subtract(int x, int y) { return x - y; }