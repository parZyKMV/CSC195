#include <iostream>

class Human
{
public:
    Human()
    {
        std::cout << "constructor\n";
        m_count++;
    }
    Human(std::string name, unsigned short age) :
        m_name{ name },
        m_age{ age }
    {
        std::cout << "constructor\n";
        m_count++;
    }
    Human()
    {
        std::cout << "constructor\n";
        m_count--;
    }

    int getCount() { return m_count };

private:
    std::string m_name;
    unsigned short m_age = 0;
    static int m_count;
    static const float m_tax;

};

void feet()
{
    std::cout << "Feet\n";
}
