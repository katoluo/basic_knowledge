#include <thread>
#include <iostream>
#include <functional>

void func(int a, double b)
{
  std::cout << a << " " << b << std::endl;
}

int main(int argc, char *argv[])
{
  std::thread t1(std::bind(func, 1, 2.0));
  std::thread t2([](int a, double b) {
      std::cout << a << " " << b << std::endl;
  }, 10, 2.1);
  t1.join();
  t2.join();

  return 0;
}
