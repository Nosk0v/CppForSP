#include <iostream>

const int ROWS = 3;
const int COLS = 4;

void replacePositiveWithNegatives(int array[][COLS])
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (array[i][j] > 0)
            {
                array[i][j] = -array[i][j];
            }
        }
    }
}

void replaceSmallerWithNumber(int array[][COLS], int number)
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (array[i][j] < number)
            {
                array[i][j] = number;
            }
        }
    }
}

void replaceInRangeWithZero(int array[][COLS], int a, int b)
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (array[i][j] >= a && array[i][j] <= b)
            {
                array[i][j] = 0;
            }
        }
    }
}

void replaceNegativeNonMultipleOfThree(int array[][COLS])
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (array[i][j] < 0 && array[i][j] % 3 != 0)
            {
                array[i][j] = -array[i][j];
            }
        }
    }
}

void doubleSmallerThan(int array[][COLS], int number)
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (array[i][j] < number)
            {
                array[i][j] *= 2;
            }
        }
    }
}

double calculateAverage(int array[][COLS])
{
    double sum = 0.0;
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            sum += array[i][j];
        }
    }
    return sum / (ROWS * COLS);
}

double calculateAverageOfNegatives(int array[][COLS])
{
    double sum = 0.0;
    int count = 0;
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (array[i][j] < 0)
            {
                sum += array[i][j];
                ++count;
            }
        }
    }
    if (count == 0)
    {
        return 0.0;
    }
    return sum / count;
}

int countOddNumbers(int array[][COLS])
{
    int count = 0;
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (array[i][j] % 2 != 0)
            {
                ++count;
            }
        }
    }
    return count;
}

int sumInRange(int array[][COLS], int a, int b)
{
    int sum = 0;
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (array[i][j] >= a && array[i][j] <= b)
            {
                sum += array[i][j];
            }
        }
    }
    return sum;
}

int sumMultiplesOfNine(int array[][COLS])
{
    int sum = 0;
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (array[i][j] % 9 == 0)
            {
                sum += array[i][j];
            }
        }
    }
    return sum;
}

void printArray(int array[][COLS])
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int array[ROWS][COLS] = {
        {3, -4, 8, 10},
        {-2, 15, -9, 7},
        {12, -6, 4, -11}};

    std::cout << "Original array:" << std::endl;
    printArray(array);

    replacePositiveWithNegatives(array);
    std::cout << "\n1. Replaced positives with negatives:" << std::endl;
    printArray(array);

    replaceSmallerWithNumber(array, 8);
    std::cout << "\n2. Replaced smaller elements with 8:" << std::endl;
    printArray(array);

    replaceInRangeWithZero(array, 1, 5);
    std::cout << "\n3. Replaced elements in range [1, 5] with zero:" << std::endl;
    printArray(array);

    replaceNegativeNonMultipleOfThree(array);
    std::cout << "\n4. Replaced negative non-multiples of three with positives:" << std::endl;
    printArray(array);

    doubleSmallerThan(array, 8);
    std::cout << "\n5. Doubled elements smaller than 8:" << std::endl;
    printArray(array);

    std::cout << "\n6. Average of all elements: " << calculateAverage(array) << std::endl;
    std::cout << "7. Average of negative elements: " << calculateAverageOfNegatives(array) << std::endl;
    std::cout << "8. Count of odd numbers: " << countOddNumbers(array) << std::endl;
    std::cout << "9. Sum of elements in range [1, 5]: " << sumInRange(array, 1, 5) << std::endl;
    std::cout << "10. Sum of multiples of 9: " << sumMultiplesOfNine(array) << std::endl;

    return 0;
}