#include <iostream>
#include <vector>
#include <string>

class Edition {
public:
    virtual void printInfo() const = 0;
    virtual bool searchByAuthor(const std::string& author) const = 0;
    virtual ~Edition() {}
};

class Book : public Edition {
private:
    std::string title;
    std::string author;
    int year;
    std::string publisher;

public:
    Book(const std::string& _title, const std::string& _author, int _year, const std::string& _publisher) 
        : title(_title), author(_author), year(_year), publisher(_publisher) {}

    virtual void printInfo() const override {
        std::cout << "Книга: " << title << ", автор: " << author << ", год издания: " << year << ", издательство: " << publisher << std::endl;
    }

    virtual bool searchByAuthor(const std::string& targetAuthor) const override {
        return author == targetAuthor;
    }
};

class Article : public Edition {
private:
    std::string title;
    std::string author;
    std::string journal;
    int year;
    int number;

public:
    Article(const std::string& _title, const std::string& _author, const std::string& _journal, int _year, int _number) 
        : title(_title), author(_author), journal(_journal), year(_year), number(_number) {}

    virtual void printInfo() const override {
        std::cout << "Статья: " << title << ", автор: " << author << ", год издания: " << year << ", журнал: " << journal << ", номер: " << number << std::endl;
    }

    virtual bool searchByAuthor(const std::string& targetAuthor) const override {
        return author == targetAuthor;
    }
};

class OnlineResource : public Edition {
private:
    std::string title;
    std::string author;
    std::string link;
    std::string annotation;

public:
    OnlineResource(const std::string& _title, const std::string& _author, const std::string& _link, const std::string& _annotation) 
        : title(_title), author(_author), link(_link), annotation(_annotation) {}

    virtual void printInfo() const override {
        std::cout << "Онлайн-ресурс: " << title << ", автор: " << author << ", ссылка: " << link << std::endl;
    }

    virtual bool searchByAuthor(const std::string& targetAuthor) const override {
        return author == targetAuthor;
    }
};

int main() {
    std::vector<Edition*> catalog;

    // Добавление изданий в каталог
    catalog.push_back(new Book("Война и мир", "Лев Толстой", 1869, "Москва"));
    catalog.push_back(new Article("Алгоритмы машинного обучения", "Питер Норвиг", "Журнал МО", 2020, 3));
    catalog.push_back(new OnlineResource("Документация по C++", "Бьярне Страуструп", "http://www.cplusplus.com/", "Подробное руководство по C++"));

    // Вывод информации о каталоге и поиск изданий по автору
    std::cout << "Каталог:" << std::endl;
    for (Edition* edition : catalog) {
        edition->printInfo();
        if (edition->searchByAuthor("Бьярне Страуструп")) {
            std::cout << "Это издание написано Бьярне Страуструпом." << std::endl;
        }
    }

    // Освобождение памяти
    for (Edition* edition : catalog) {
        delete edition;
    }

    return 0;
}