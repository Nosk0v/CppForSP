#include <iostream>
#include <algorithm>

template<typename T = int>
class Array {
protected:
    int size;
    T* array;

public:
    Array(int size) : size(size) {
        array = new T[size];
        for (int i = 0; i < size; ++i) {
            array[i] = T(); // заполнение массива нулями
        }
    }

    ~Array() {
        delete[] array;
    }

    void display() const {
        for (int i = 0; i < size; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    void sort() {
        std::sort(array, array + size);
    }

    void addElement(const T& element) {
        T* newArray = new T[size + 1];
        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }
        newArray[size] = element;
        delete[] array;
        array = newArray;
        ++size;
    }
};

int main() {
    Array<int> intArray(5);
    intArray.display(); // вывод массива до добавления элемента

    intArray.addElement(10);
    intArray.display(); // вывод массива после добавления элемента

    intArray.sort();
    intArray.display(); // вывод отсортированного массива

    Array<double> doubleArray(4);
    doubleArray.addElement(3.14);
    doubleArray.addElement(1.618);
    doubleArray.display(); // вывод массива вещественных чисел
    return 0;
}