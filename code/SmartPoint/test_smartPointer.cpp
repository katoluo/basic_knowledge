#include <iostream>
#include <string>
#include "./smartPointer.hpp"

class Person {
public:
  Person(int age = 0, std::string name = "")
    : _age(age), _name(name) {}

  void show() const {
    std::cout << _name << "今年" << _age << std::endl;
  }

  ~Person() {

  }

private:
  int _age;
  std::string _name;
};

int main(void)
{
  SmartPointer<int> p(new int(5));
  std::cout << *p << std::endl;

  SmartPointer<Person> p1(new Person(22, "kato"));
  SmartPointer<Person> p2(p1);

  SmartPointer<Person> p3(new Person(19, "aragne"));
  p2 = p3;

  //SmartPointer<Person> p4;
  //p4->show();

  (*p1).show();
  p2->show();

  return 0;
}
