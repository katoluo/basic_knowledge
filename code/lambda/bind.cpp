#include <iostream>
#include <functional>
#include <string>

using std::placeholders::_1;

bool check_size(const std::string &s, std::string::size_type sz)
{
  return s.size() >= sz;
}

int main(void)
{
  std::string str = "Hello world";
  auto newCallable = std::bind(check_size, str, _1);


  bool flag = newCallable(20);

  if (flag) {
    std::cout << "Hello world" << std::endl;
  }

  return 0;
}
