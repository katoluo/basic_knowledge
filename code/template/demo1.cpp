#include <iostream>

class Point;
std::ostream& operator<< (std::ostream &os, const Point &rhs);

class Point {
  int m_x;
  int m_y;

public:
  friend std::ostream& operator<< (std::ostream &os, const Point &rhs);
  Point(int x, int y) : m_x(x), m_y(y) { }
  
  Point operator+(const Point &rhs) {
    return Point(this->m_x + rhs.m_x, this->m_y + rhs.m_y);
  }
};

std::ostream& operator<< (std::ostream &os, const Point &rhs)
{
  os << "(" << rhs.m_x << "," << rhs.m_y << ")";
  return os;
}

/*
Point add(Point a, Point b) {
  return a + b;
}

int add(int a, int b) {
  return a + b;
}

double add(double a, double b) {
  return a + b;
}
*/

template<typename T>
T add(T a, T b) {
  return a + b;
}

int main(void)
{
  std::cout << add<int>(1, 2) << std::endl;
  std::cout << add<double>(1.2, 3.6) << std::endl;
  std::cout << add<Point>(Point(1, 2), Point(4, 3)) << std::endl;

  return 0;
}
