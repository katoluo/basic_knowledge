#include <memory>
#include <cassert>

template <typename T>
class SmartPointer {
private:
  T      *_ptr;
  size_t *_reference_count;

public:
  // 构造函数
  SmartPointer(T *ptr = 0)
    : _ptr(ptr), _reference_count(new size_t) {
      if (_ptr)
        *_reference_count = 1;
      else 
        *_reference_count = 0;
    }
  // 拷贝构造函数
  SmartPointer(const SmartPointer &rhs)
    : _ptr(rhs._ptr), _reference_count(rhs._reference_count) {
      ++(*_reference_count);
    }

  // 拷贝赋值运算符
  SmartPointer& operator=(const SmartPointer &rhs) {
    if (_ptr == rhs._ptr) {
      return *this;
    }
    if (this->_ptr) {
      (*this->_reference_count)--;
      if (this->_reference_count == 0) {
        delete this->_ptr;
        delete this->_reference_count;
      }
    }
    this->_ptr = rhs._ptr;
    this->_reference_count = rhs._reference_count;
    ++(*this->_reference_count);
    return *this;
  }

  T& operator*() {
    assert(_ptr);
    return *_ptr;
  }

  T* operator->() {
    assert(_ptr);
    return _ptr;
  }

  ~SmartPointer() {
    if (--(*_reference_count) == 0) {
      delete _ptr;
      delete _reference_count;
      _ptr = nullptr;
      _reference_count = nullptr;
    }
  }
};
