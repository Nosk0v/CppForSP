#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Функция для чтения строк из файла
std::vector<std::string> readLinesFromFile(const std::string &filename)
{
    std::vector<std::string> lines;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return lines;
    }
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

// Функция для подсчета количества строк, начинающихся с заданной буквы
int countLinesStartingWithLetter(const std::vector<std::string> &lines, char letter)
{
    int count = 0;
    for (const auto &line : lines)
    {
        if (!line.empty() && line[0] == letter)
        {
            count++;
        }
    }
    return count;
}

// Функция для подсчета количества строк, начинающихся и заканчивающихся одной буквой
int countLinesStartingAndEndingWithSameLetter(const std::vector<std::string> &lines)
{
    int count = 0;
    for (const auto &line : lines)
    {
        if (!line.empty() && line.front() == line.back())
        {
            count++;
        }
    }
    return count;
}

// Функция для поиска самой длинной строки и ее длины
std::pair<std::string, int> findLongestLine(const std::vector<std::string> &lines)
{
    std::pair<std::string, int> longest("", 0);
    for (const auto &line : lines)
    {
        if (line.length() > longest.second)
        {
            longest.first = line;
            longest.second = line.length();
        }
    }
    return longest;
}

// Функция для поиска самой короткой строки и ее длины
std::pair<std::string, int> findShortestLine(const std::vector<std::string> &lines)
{
    std::pair<std::string, int> shortest("", std::numeric_limits<int>::max());
    for (const auto &line : lines)
    {
        if (line.length() < shortest.second)
        {
            shortest.first = line;
            shortest.second = line.length();
        }
    }
    return shortest;
}

// Функция для поиска номера самой длинной строки
int findLongestLineIndex(const std::vector<std::string> &lines)
{
    int index = -1;
    int maxLength = 0;
    for (int i = 0; i < lines.size(); ++i)
    {
        if (lines[i].length() > maxLength)
        {
            index = i;
            maxLength = lines[i].length();
        }
    }
    return index;
}

// Функция для поиска номера самой короткой строки
int findShortestLineIndex(const std::vector<std::string> &lines)
{
    int index = -1;
    int minLength = std::numeric_limits<int>::max();
    for (int i = 0; i < lines.size(); ++i)
    {
        if (lines[i].length() < minLength)
        {
            index = i;
            minLength = lines[i].length();
        }
    }
    return index;
}

void separateNumbers(const std::string &inputFileName, const std::string &evenFileName, const std::string &oddFileName)
{
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file: " << inputFileName << std::endl;
        return;
    }

    std::ofstream evenFile(evenFileName);
    if (!evenFile.is_open())
    {
        std::cerr << "Unable to open/create the file: " << evenFileName << std::endl;
        return;
    }

    std::ofstream oddFile(oddFileName);
    if (!oddFile.is_open())
    {
        std::cerr << "Unable to open/create the file: " << oddFileName << std::endl;
        return;
    }

    int number;
    while (inputFile >> number)
    {
        if (number % 2 == 0)
        {
            evenFile << number << std::endl;
        }
        else
        {
            oddFile << number << std::endl;
        }
    }

    std::cout << "Numbers separated successfully." << std::endl;
}

void writeSquaresToFile(const std::string &filename, int n)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Unable to open/create the file: " << filename << std::endl;
        return;
    }

    for (int i = 1; i <= n; ++i)
    {
        int square = i * i;
        file.write(reinterpret_cast<const char *>(&square), sizeof(square));
    }

    std::cout << "Squares written to the file: " << filename << std::endl;
}

void printOddComponents(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return;
    }

    int number;
    int componentNumber = 0;
    while (file.read(reinterpret_cast<char *>(&number), sizeof(number)))
    {
        ++componentNumber;
        if (componentNumber % 2 != 0)
        {
            std::cout << "Component " << componentNumber << ": " << number << std::endl;
        }
    }
}

int main()
{
    // Чтение строк из файла
    std::vector<std::string> lines = readLinesFromFile("input.txt");

    // Пример использования функций для задач
    char letter = 'A';
    int countLinesStartingWithLetterResult = countLinesStartingWithLetter(lines, letter);
    std::cout << "Number of lines starting with letter '" << letter << "': " << countLinesStartingWithLetterResult << std::endl;

    int countLinesStartingAndEndingWithSameLetterResult = countLinesStartingAndEndingWithSameLetter(lines);
    std::cout << "Number of lines starting and ending with the same letter: " << countLinesStartingAndEndingWithSameLetterResult << std::endl;

    std::pair<std::string, int> longestLine = findLongestLine(lines);
    std::cout << "Longest line: " << longestLine.first << ", Length: " << longestLine.second << std::endl;

    std::pair<std::string, int> shortestLine = findShortestLine(lines);
    std::cout << "Shortest line: " << shortestLine.first << ", Length: " << shortestLine.second << std::endl;

    int longestLineIndex = findLongestLineIndex(lines);
    std::cout << "Index of the longest line: " << longestLineIndex + 1 << std::endl;

    int shortestLineIndex = findShortestLineIndex(lines);
    std::cout << "Index of the shortest line: " << shortestLineIndex + 1 << std::endl;

    std::string inputFileName = "input.txt";
    std::string evenFileName = "even.txt";
    std::string oddFileName = "odd.txt";

    std::string filename = "squares.bin";
    int n = 10; // Количество натуральных чисел

    writeSquaresToFile(filename, n);
    std::cout << "Components with odd ordinal numbers:" << std::endl;
    printOddComponents(filename);

    return 0;
}
