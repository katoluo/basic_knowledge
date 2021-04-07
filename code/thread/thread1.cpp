#include <thread>
#include <iostream>
#include <string>


void func(int i, char c, const std::string &s)
{
  // do some work
  std::cout << i << " " << c << " " << s << std::endl;
}

int main(void)
{
  std::thread t(func, 10, 'a', "Hello world");
  std::thread t1(std::move(t));
  std::cout << t1.get_id() << std::endl;
  //  join函数将会阻塞线程,知道线程函数执行结束，如果有返回值将被忽略
  t1.join();

  return 0;
}
