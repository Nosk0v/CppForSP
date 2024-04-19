#include <iostream>
#include <stdexcept>

class Complex {
private:
    double re;
    double im;
    static int counter;

public:
    Complex(double re, double im) : re(re), im(im) {
        counter++;
    }

    void print() const {
        if (im >= 0)
            std::cout << re << "+i" << im << std::endl;
        else
            std::cout << re << "-i" << -im << std::endl;
    }

    static int getCounter() {
        return counter;
    }

    static Complex add(const Complex& a, const Complex& b) {
        return Complex(a.re + b.re, a.im + b.im);
    }

    static Complex subtract(const Complex& a, const Complex& b) {
        return Complex(a.re - b.re, a.im - b.im);
    }

    static Complex multiply(const Complex& a, const Complex& b) {
        return Complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
    }

    static Complex divide(const Complex& a, const Complex& b) {
        if (b.re == 0 && b.im == 0)
            throw std::runtime_error("Division by zero");
        double denominator = b.re * b.re + b.im * b.im;
        double re = (a.re * b.re + a.im * b.im) / denominator;
        double im = (a.im * b.re - a.re * b.im) / denominator;
        return Complex(re, im);
    }

    double getRe() const {
        return re;
    }
};

int Complex::counter = 0;

class Real : public Complex {
public:
    Real(double r) : Complex(r, 0) {}

    void print() const {
        std::cout << getRe() << std::endl; // Используем открытое наследование, чтобы получить доступ к getRe()
    }

    static Real add(const Real& a, const Real& b) {
        return Real(a.getRe() + b.getRe());
    }

    static Real subtract(const Real& a, const Real& b) {
        return Real(a.getRe() - b.getRe());
    }

    static Real multiply(const Real& a, const Real& b) {
        return Real(a.getRe() * b.getRe());
    }

    static Real divide(const Real& a, const Real& b) {
        if (b.getRe() == 0)
            throw std::runtime_error("Division by zero");
        return Real(a.getRe() / b.getRe()); 
    }
};

int main() {
    return 0;
}