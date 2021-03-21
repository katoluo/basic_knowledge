#include "./StrVec.h"

void StrVec::push_back(const std::string &s)
{
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
  auto data = alloc.allocate(e - b);
  return { data, std::uninitialized_copy(b, e, data) };
}


void StrVec::free()
{
  // 不能传递给deallocate一个空指针，如果elements为0,函数什么也不做
  if (elements) {
    // 逆序销毁旧元素
    for (auto p = first_free; p != elements; )
      alloc.destroy(--p);
    alloc.deallocate(elements, cap - elements);
  }
}

StrVec::StrVec(const StrVec &s)
{
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::~StrVec()
{
  free();
}

StrVec& StrVec::operator=(const StrVec &rhs)
{
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  this->free();
  this->elements = data.first;
  this->first_free = this->cap = data.second;
  return *this;
}

void StrVec::alloc_n_move(size_t new_cap)
{
  auto newdata = alloc.allocate(new_cap);
  auto dest = newdata;
  auto elem = elements;
  for (size_t i = 0; i != elem->size(); ++i)
    alloc.construct(dest++, std::move(*elem++));
  free();
  elements = newdata;
  first_free = dest;
  cap = elements + new_cap;
}

void StrVec::reallocate()
{
  auto newcapacity = size() ? 2 * size() : 1;
  alloc_n_move(newcapacity);
}

void StrVec::reserve(size_t new_cap)
{
  if (new_cap <= capacity()) return;
  alloc_n_move(new_cap);
}

void StrVec::resize(size_t count)
{
  resize(count, std::string());
}

void StrVec::resize(size_t count, const std::string &s)
{
  if (count > size()) {
    if (count > capacity()) reserve(count * 2);
    for (size_t i = size(); i != count; ++i)
      alloc.construct(first_free++, s);
  }
  else if (count < size()) {
    while (first_free != elements + count)
      alloc.destroy(--first_free);
  }
}


