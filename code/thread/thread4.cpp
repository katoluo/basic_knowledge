#include <thread>
#include <iostream>

struct A {
  void operator()() const
  {
    std::cout << 1;
  }
};

int main(void)
{
  A a;
  std::thread t1(a);  // 调用A::operator()
  // std;::thread t(A()); 
}
