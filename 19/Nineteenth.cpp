#include <iostream>
 
class Person 
{
private:
    std::string name;
    unsigned age;
public:
    Person(std::string p_name, unsigned p_age)
    { 
        name = p_name; 
        if (p_age > 0 && p_age < 110) 
            age = p_age;
        else
            age = 18;   // если значение некорректное, устанавливаем значение по умолчанию
    }
    
    void print() 
    {
        std::cout << "Name: " << name << "\tAge: " << age << std::endl;
    }
    
    void setAge(unsigned p_age) 
    {
        if (p_age > 0 && p_age < 110) 
            age = p_age;
    }
    
    std::string getName()
    {
        return name;
    }
    
    unsigned getAge()
    {
        return age;
    }
};
 
int main()
{
    Person tom{"Tom", 38};
    
    // изменяем возраст
    tom.setAge(22);
    tom.setAge(123);
    tom.print();    // Name: Tom   Age: 22
 
    //отдельно получаем имя
    std::cout << "Person name: " << tom.getName() << std::endl;
    
    return 0;
}