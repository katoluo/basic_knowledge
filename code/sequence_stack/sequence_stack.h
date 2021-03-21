#ifndef __SQ_STACK_H__
#define __SQ_STACK_H__

#include <iostream>

typedef char ElemType;
const int stack_size = 100;

class SqStack {
public:
  SqStack();
  SqStack(const SqStack&) = delete;
  SqStack& operator= (const SqStack&) = delete;
  ~SqStack();

private:
  ElemType *data;
  int top;
};




#endif
