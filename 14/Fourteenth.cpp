#include <iostream>

void replacePositiveWithNegatives(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (array[i] > 0)
        {
            array[i] = -array[i];
        }
    }
}

void replaceSmallerWithNumber(int array[], int size, int number)
{
    for (int i = 0; i < size; ++i)
    {
        if (array[i] < number)
        {
            array[i] = number;
        }
    }
}

void replaceInRangeWithZero(int array[], int size, int a, int b)
{
    for (int i = 0; i < size; ++i)
    {
        if (array[i] >= a && array[i] <= b)
        {
            array[i] = 0;
        }
    }
}

void replaceNegativeNonMultipleOfThree(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (array[i] < 0 && array[i] % 3 != 0)
        {
            array[i] = -array[i];
        }
    }
}

void doubleSmallerThan(int array[], int size, int number)
{
    for (int i = 0; i < size; ++i)
    {
        if (array[i] < number)
        {
            array[i] *= 2;
        }
    }
}

double calculateAverage(int array[], int size)
{
    if (size == 0)
    {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 0; i < size; ++i)
    {
        sum += array[i];
    }
    return sum / size;
}

double calculateAverageOfNegatives(int array[], int size)
{
    if (size == 0)
    {
        return 0.0;
    }
    double sum = 0.0;
    int count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (array[i] < 0)
        {
            sum += array[i];
            ++count;
        }
    }
    if (count == 0)
    {
        return 0.0;
    }
    return sum / count;
}

int countOddNumbers(int array[], int size)
{
    int count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (array[i] % 2 != 0)
        {
            ++count;
        }
    }
    return count;
}

int sumInRange(int array[], int size, int a, int b)
{
    int sum = 0;
    for (int i = 0; i < size; ++i)
    {
        if (array[i] >= a && array[i] <= b)
        {
            sum += array[i];
        }
    }
    return sum;
}

int sumMultiplesOfNine(int array[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; ++i)
    {
        if (array[i] % 9 == 0)
        {
            sum += array[i];
        }
    }
    return sum;
}

int main()
{
    const int size = 10;
    int array[size] = {3, -4, 8, 10, -2, 15, -9, 7, 12, -6};

    replacePositiveWithNegatives(array, size);
    std::cout << "1. Replaced positives with negatives: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    replaceSmallerWithNumber(array, size, 5);
    std::cout << "2. Replaced elements smaller than 5: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    replaceInRangeWithZero(array, size, -3, 7);
    std::cout << "3. Replaced elements in range [-3, 7] with zeros: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    replaceNegativeNonMultipleOfThree(array, size);
    std::cout << "4. Replaced negative elements not multiple of 3: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    doubleSmallerThan(array, size, 8);
    std::cout << "5. Doubled elements smaller than 8: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "6. Average of all elements: " << calculateAverage(array, size) << std::endl;
    std::cout << "7. Average of negative elements: " << calculateAverageOfNegatives(array, size) << std::endl;
    std::cout << "8. Count of odd numbers: " << countOddNumbers(array, size) << std::endl;
    std::cout << "9. Sum of elements in range [0, 5]: " << sumInRange(array, size, 0, 5) << std::endl;
    std::cout << "10. Sum of multiples of 9: " << sumMultiplesOfNine(array, size) << std::endl;

    return 0;
}