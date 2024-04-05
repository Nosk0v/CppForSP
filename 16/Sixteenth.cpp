#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

void insertAfterEachOccurrence(char c2, char cl, std::string& str) {
    size_t pos = str.find(c2);
    while (pos != std::string::npos) {
        str.insert(pos + 1, 1, cl);
        pos = str.find(c2, pos + 2); 
    }
}

void insertAfterEachSubstring(const std::string& str1, const std::string& str2, std::string& str) {
    size_t pos = str.find(str1);
    while (pos != std::string::npos) {
        str.insert(pos + str1.length(), str2);
        pos = str.find(str1, pos + str2.length() + 1);
    }
}

int countVowels(const std::string& str) {
    int count = 0;
    std::string vowels = "аеёиоуыэюя";
    for (char c : str) {
        if (vowels.find(tolower(c)) != std::string::npos) {
            ++count;
        }
    }
    return count;
}

bool hasAdjacentDuplicates(const std::string& str) {
    for (size_t i = 0; i < str.length() - 1; ++i) {
        if (str[i] == str[i + 1]) {
            return true;
        }
    }
    return false;
}

void doubleOccurrencesOfChar(char letter, std::string& str) {
    size_t pos = str.find(letter);
    while (pos != std::string::npos) {
        str.insert(pos, 1, letter); 
        pos = str.find(letter, pos + 2); 
    }
}

void removeChar(char c, std::string& str) {
    str.erase(std::remove(str.begin(), str.end(), c), str.end());
}

void removeSubstring(const std::string& substr, std::string& str) {
    size_t pos = str.find(substr);
    while (pos != std::string::npos) {
        str.erase(pos, substr.length());
        pos = str.find(substr, pos); 
    }
}

void replaceSubstring(const std::string& oldStr, const std::string& newStr, std::string& str) {
    size_t pos = str.find(oldStr);
    while (pos != std::string::npos) {
        str.replace(pos, oldStr.length(), newStr);
        pos = str.find(oldStr, pos + newStr.length()); 
    }
}

int countDifferentCharacters(const std::string& str) {
    std::string uniqueChars = "";
    for (char c : str) {
        if (uniqueChars.find(c) == std::string::npos) {
            uniqueChars += c;
        }
    }
    return uniqueChars.length();
}

std::vector<std::string> findPalindromes(const std::string& str) {
    std::vector<std::string> palindromes;
    std::istringstream iss(str);
    std::string word;
    while (iss >> word) {
        std::string reversed = word;
        std::reverse(reversed.begin(), reversed.end());
        if (word == reversed) {
            palindromes.push_back(word);
        }
    }
    return palindromes;
}

int main() {
    std::string text = "А роза упала на лапу Азора";
    std::cout << "1. Количество гласных букв: " << countVowels(text) << std::endl;

    std::cout << "2. Есть ли два соседствующих одинаковых символа: ";
    if (hasAdjacentDuplicates(text)) {
        std::cout << "Да" << std::endl;
    } else {
        std::cout << "Нет" << std::endl;
    }

    char letter = 'a';
    doubleOccurrencesOfChar(letter, text);
    std::cout << "3. Удвоенные вхождения буквы '" << letter << "': " << text << std::endl;

    char c = 'a';
    removeChar(c, text);
    std::cout << "4. Удаление всех символов '" << c << "': " << text << std::endl;

    std::string substr = "лапу";
    removeSubstring(substr, text);
    std::cout << "5. Удаление всех подстрок '" << substr << "': " << text << std::endl;

    std::string oldStr = "роза";
    std::string newStr = "мед";
    replaceSubstring(oldStr, newStr, text);
    std::cout << "6. Замена подстроки '" << oldStr << "' на '" << newStr << "': " << text << std::endl;

    std::cout << "7. Количество различных символов: " << countDifferentCharacters(text) << std::endl;

    std::cout << "8. Слова-палиндромы в строке: ";
    std::vector<std::string> palindromes = findPalindromes(text);
    for (const auto& palindrome : palindromes) {
        std::cout << palindrome << " ";
    }
    std::cout << std::endl;

    return 0;
}