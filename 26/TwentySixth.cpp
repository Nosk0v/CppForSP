#include <iostream>

class Counter
{
public:
    Counter(int n)
    {
        value = n;
    }
    void print() const
    {
        std::cout << "value: " << value << std::endl;
    }
    Counter &operator+=(const Counter &counter)
    {
        value += counter.value;
        return *this;
    };
    Counter &operator+(const Counter &counter)
    {
        Counter copy{value}; // копируем данные текущего объекта
        return copy += counter;
    };

    // префиксные операторы
    Counter &operator++()
    {
        value += 1;
        return *this;
    }
    Counter &operator--()
    {
        value -= 1;
        return *this;
    }
    // постфиксные операторы
    Counter operator++(int)
    {
        Counter copy{*this};
        ++(*this);
        return copy;
    }
    Counter operator--(int)
    {
        Counter copy{*this};
        --(*this);
        return copy;
    }

    // Метод для получения значения value
    int getValue() const
    {
        return value;
    }

private:
    int value;
};

// Оператор вывода для объекта Counter
std::ostream &operator<<(std::ostream &stream, const Counter &counter)
{
    stream << "Value: ";
    stream << counter.getValue();
    return stream;
}

int main()
{
    // Примеры использования класса Counter
    Counter counter1{20};
    Counter counter2{10};

    counter1 += counter2;
    counter1.print(); // value: 30

    Counter counter3{counter1 + counter2};
    counter3.print(); // value: 40

    Counter c1{20};
    Counter c2 = c1++;
    c2.print(); // Value: 20
    c1.print(); // Value: 21
    --c1;
    c1.print(); // Value: 20

    Counter counter4{30};
    Counter counter5{50};
    std::cout << counter4 << std::endl; // Value: 30
    std::cout << counter5 << std::endl; // Value: 50

    return 0;
}
