#include <iostream>
#include <cmath>

class Figure
{
public:
    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void printInfo() const = 0;
    virtual ~Figure() {}
};

class Rectangle : public Figure
{
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double calculateArea() const override
    {
        return width * height;
    }

    double calculatePerimeter() const override
    {
        return 2 * (width + height);
    }

    void printInfo() const override
    {
        std::cout << "Rectangle: width = " << width << ", height = " << height
                  << ", area = " << calculateArea()
                  << ", perimeter = " << calculatePerimeter() << std::endl;
    }
};

class Circle : public Figure
{
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double calculateArea() const override
    {
        return M_PI * radius * radius;
    }

    double calculatePerimeter() const override
    {
        return 2 * M_PI * radius;
    }

    void printInfo() const override
    {
        std::cout << "Circle: radius = " << radius
                  << ", area = " << calculateArea()
                  << ", perimeter = " << calculatePerimeter() << std::endl;
    }
};

class Triangle : public Figure
{
private:
    double side1, side2, side3;

public:
    Triangle(double s1, double s2, double s3) : side1(s1), side2(s2), side3(s3) {}

    double calculateArea() const override
    {
        double p = (side1 + side2 + side3) / 2;
        return sqrt(p * (p - side1) * (p - side2) * (p - side3));
    }

    double calculatePerimeter() const override
    {
        return side1 + side2 + side3;
    }

    void printInfo() const override
    {
        std::cout << "Triangle: sides = " << side1 << ", " << side2 << ", " << side3
                  << ", area = " << calculateArea()
                  << ", perimeter = " << calculatePerimeter() << std::endl;
    }
};

int main()
{
    const int size = 3;
    Figure *figures[size];
    figures[0] = new Rectangle(5, 3);
    figures[1] = new Circle(4);
    figures[2] = new Triangle(3, 4, 5);

    for (int i = 0; i < size; ++i)
    {
        figures[i]->printInfo();
    }

    // Освобождаем память
    for (int i = 0; i < size; ++i)
    {
        delete figures[i];
    }

    return 0;
}