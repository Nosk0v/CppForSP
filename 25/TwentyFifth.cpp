#include <iostream>

class Person
{
public:
    static inline const unsigned maxAge{120};
    Person(std::string p_name, unsigned p_age)
    {
        ++count;
        name = p_name;
        if (p_age < maxAge)
            age = p_age;
    }

    static void print_count()
    {
        std::cout << "Created " << count << " objects" << std::endl;
    }

private:
    std::string name;
    unsigned age{1};
    static inline unsigned count{};
};

int main()
{
    Person tom{"Tom", 38};
    Person bob{"Bob", 42};

    Person::print_count();
    std::cout << "Max age: " << Person::maxAge << std::endl;
}