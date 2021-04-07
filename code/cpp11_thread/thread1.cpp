#include <thread>
#include <iostream>

void func()
{
  // do some work
  std::cout << "Hello Thread" << std::endl;
}

int main(void)
{
  std::thread t(func);

  t.join();


  return 0;
}
