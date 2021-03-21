#ifndef __STRVEC__
#define __STRVEC__

#include <memory>
#include <string>

class StrVec {
public:
  StrVec(): // allocator成员进行默认初始化
    elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(const StrVec &);   // 拷贝构造
  StrVec& operator= (const StrVec&);  // 拷贝赋值运算符
  ~StrVec();  // 析构函数
  void push_back(const std::string&);   // 拷贝元素
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }
  std::string* begin() const { return elements; }
  std::string* end() const { return first_free; }

  void reserve(size_t new_cap);
  void resize(size_t count);
  void resize(size_t count, const std::string&);

private:
  void chk_n_alloc() {
    if ( size() == capacity() )
      reallocate();
  }
  void free();
  void reallocate();
  void alloc_n_move(size_t new_cap);
  std::pair<std::string*, std::string*> alloc_n_copy
    (const std::string*, const std::string*);

private:
  std::allocator<std::string> alloc;   // 分配元素
  // 被添加元素的函数所使用
  std::string *elements;  // 指向数组首元素的指针
  std::string *first_free; // 指向数组第一个空闲元素的指针
  std::string *cap;   // 指向数组尾后位置的指针

};





#endif
