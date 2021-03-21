#ifndef __HASPTR__
#define __HASPTR__


#include <string>

class HasPtr
{
  public:
    HasPtr(const std::string &s = std::string())
      : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &p)
      : ps(new std::string(*p.ps)), i(p.i) { }

    HasPtr& operator= (const HasPtr &);
    ~HasPtr() { delete this->ps; }

  private:
    std::string *ps;
    int i;

};

HasPtr&
HasPtr::operator=(const HasPtr &r)
{
  if (this == &r)
    return *this;

  delete this->ps;
  this->i = r.i;
  this->ps = new std::string(*r.ps);
  return *this;
}




#endif
