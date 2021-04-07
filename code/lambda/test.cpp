#include <iostream>

int main(void)
{
  auto f = [](int i) { return i < 0 ? -i : i; };
  auto f2 = [](int i) ->int {
    if (i < 0) return -i;
    else return i;
  };

  std::cout << f(-2) << std::endl;
  std::cout << f2(2) << std::endl;


  return 0;
}
