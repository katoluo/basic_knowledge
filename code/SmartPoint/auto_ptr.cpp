#include <iostream>
#include <memory>

class Person {
public:
  Person() {
    std::cout << "Person()" << std::endl;
  }
  ~Person() {
    std::cout << "~Person()" << std::endl;
  }
};

int main(void)
{
  std::auto_ptr<Person> p(new Person());
  
  std::shared_ptr<int> p1(new int(3));
  std::shared_ptr<int> p2 = std::make_shared<int>(3);

  return 0;
}
