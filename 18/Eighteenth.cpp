#include <iostream>
 
class Person 
{
public:
    std::string name;
    unsigned age;
    void print() 
    {
        std::cout << "Name: " << name << "\tAge: " << age << std::endl;
    }
};

int main()
{
    Person person;
    Person *ptr = &person;
    
    // обращаемся к полям и функции объекта через указатель
    ptr->name = "Tom";
    ptr->age = 22;
    ptr->print();
    
    // обращаемся к полям объекта
    std::cout << "Name: " << person.name << "\tAge: " << person.age << std::endl;
    
    // устанавливаем значения полей класса
    person.name = "Bob";
    person.age = 42;
    
    // получаем значения полей
    std::string username = person.name;
    unsigned userage = person.age;
    
    // выводим полученные данные на консоль
    std::cout << "Name: " << username << "\tAge: " << userage << std::endl;
    
    return 0;
}
