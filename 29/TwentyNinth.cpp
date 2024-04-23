#include <iostream>
int main()
{
    class Function
    {
    public:
        virtual double calculate(double x) const = 0;
        virtual void printInfo() const = 0;
    };

    class Line : public Function
    {
    private:
        double a;
        double b;

    public:
        Line(double _a, double _b) : a(_a), b(_b) {}

        virtual double calculate(double x) const override
        {
            return a * x + b;
        }

        virtual void printInfo() const override
        {
            std::cout << "Function type: Line (y = " << a << "x + " << b << ")" << std::endl;
        }
    };
    class Quad : public Function
    {
    private:
        double a;
        double b;
        double c;

    public:
        Quad(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

        virtual double calculate(double x) const override
        {
            return a * x * x + b * x + c;
        }

        virtual void printInfo() const override
        {
            std::cout << "Function type: Quad (y = " << a << "x^2 + " << b << "x + " << c << ")" << std::endl;
        }
    };
    class Hyperbola : public Function
    {
    private:
        double a;

    public:
        Hyperbola(double _a) : a(_a) {}

        virtual double calculate(double x) const override
        {
            if (x == 0)
            {
                std::cerr << "Error: Division by zero!" << std::endl;
                return 0; // Обработка деления на ноль
            }
            return a / x;
        }

        virtual void printInfo() const override
        {
            std::cout << "Function type: Hyperbola (y = " << a << "/x)" << std::endl;
        }
    };
    return 0;
}