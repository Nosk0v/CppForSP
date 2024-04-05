#include <iostream>
#include <string>
#include <vector>
#include <cctype>

void printAllDigits(const std::string& text) {
    std::cout << "Цифры в тексте: ";
    for (char c : text) {
        if (std::isdigit(c)) {
            std::cout << c << " ";
        }
    }
    std::cout << std::endl;
}

void printOddDigits(const std::string& text) {
    std::cout << "Нечетные цифры в тексте: ";
    for (char c : text) {
        if (std::isdigit(c) && (c - '0') % 2 != 0) {
            std::cout << c << " ";
        }
    }
    std::cout << std::endl;
}

int countDigits(const std::string& text) {
    int count = 0;
    for (char c : text) {
        if (std::isdigit(c)) {
            ++count;
        }
    }
    return count;
}

int sumDigits(const std::string& text) {
    int sum = 0;
    for (char c : text) {
        if (std::isdigit(c)) {
            sum += (c - '0');
        }
    }
    return sum;
}

char maxDigit(const std::string& text) {
    char max = '0';
    for (char c : text) {
        if (std::isdigit(c) && c > max) {
            max = c;
        }
    }
    return max;
}

void replaceOddDigitsWithMin(const std::string& text) {
    char minDigit = '9';
    for (char c : text) {
        if (std::isdigit(c) && (c - '0') % 2 != 0 && c < minDigit) {
            minDigit = c;
        }
    }
    std::cout << "Замена всех нечетных цифр на минимальную цифру '" << minDigit << "': ";
    for (char c : text) {
        if (std::isdigit(c)) {
            if ((c - '0') % 2 != 0) {
                std::cout << minDigit << " ";
            } else {
                std::cout << c << " ";
            }
        } else {
            std::cout << c << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::string text = "abc12345de6f789ghi0jkl";
    
    printAllDigits(text);
    printOddDigits(text);
    std::cout << "Количество цифр в тексте: " << countDigits(text) << std::endl;
    std::cout << "Сумма всех цифр в тексте: " << sumDigits(text) << std::endl;
    std::cout << "Наибольшая цифра в тексте: " << maxDigit(text) << std::endl;
    replaceOddDigitsWithMin(text);

    return 0;
}