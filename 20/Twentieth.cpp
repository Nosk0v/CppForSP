#include <iostream>
 
class Person 
{
private:
    std::string name;
    unsigned age;
public:
    // Constructor with default age value
    Person(std::string p_name, unsigned p_age = 18) : name(p_name), age(p_age) {}
    
    // Function to print person details
    void print() 
    {
        std::cout << "Name: " << name << "\tAge: " << age << std::endl;
    }
};
 
int main()
{
    Person tom("Tom", 38);
    tom.print();    // Name: Tom   Age: 38

    Person bob("Bob");
    bob.print();    // Name: Bob   Age: 18
}
