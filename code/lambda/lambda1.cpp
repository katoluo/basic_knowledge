#include <iostream>

int main(int argc, char *argv[])
{
  size_t v1 = 42;

  //auto f1 = [&v1] { return ++v1; };

  auto f2 = [v1]() mutable { return ++v1; };

  std::cout << "brfore lambda v1: " << v1 << std::endl; // 42
  std::cout << "lambda f1:" << f2() << std::endl; // 43
  std::cout << "after lambda v1: " << v1 << std::endl; // 42

  return 0;
}
