#include "./linked_list.h"

std::ostream&
operator<< (std::ostream &os, const LinkList &L)
{
  Node *p = nullptr;

  p = L._head->next;
  while (p != nullptr) {
    os << p->data;
    p = p->next;
  }
  return os;
}


bool
LinkList::CreatList()
{
  _head = new Node();
  _head->next = nullptr;
  if (_head)
    _tail = _head;
  else {
    std::cout << "CreatList:: creat node failed" << std::endl;
    return false;
  }
  return true;
}

// 构造函数
LinkList::LinkList()
{
  CreatList();
}


void
LinkList::DestroyList()
{
#ifdef DEBUGGER
  std::cout << "destrcut starting..." << std::endl;
#endif
  Node *p = _head;

  Node *q = nullptr;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  _head = _tail = nullptr;
#ifdef DEBUGGER
  std::cout << "destruct end" << std::endl;
#endif
}

// 析构函数-------------------------------------------------------
LinkList::~LinkList()
{
  DestroyList();
}


// 头插法----------------------------------------------------------
bool
LinkList::HeadInsert(const ElemType &e)
{
  Node *p = new Node(e);

  if (p) {
    if (_head->next == nullptr)
      _tail = p;
    p->next = _head->next;
    _head->next = p;
  }
  else {
    std::cout << "HeadInsert:: creat node failed" << std::endl;
    return false;
  }
  return true;
}

// 尾插法----------------------------------------------------------
bool
LinkList::TailInsert(const ElemType &e)
{
  Node *p = new Node(e);

  if (p) {
    _tail->next = p;
    _tail = p;
  }
  else {
    std::cout << "TailInsert:: creat node failed" << std::endl;
    return false;
  }
  return true;
}

int 
LinkList::GetListLength()
{
  Node *p = _head->next;
  int i = 0;
  while (p != nullptr) {
    ++i;
    p = p->next;
  }
  return i;
}

Node*
LinkList::GetNode(int i)
{
  if (i < 1 || i > GetListLength()) {
    std::cout << "GetNode:: parameter error" << std::endl;
    return nullptr;
  }

  Node *p = _head;
  while (i > 0) {
    if (p->next == nullptr) {
      std::cout << "GetNode:: i->position error" << std::endl;
      return nullptr;
    }
    p = p->next;
    --i;
  }
  return p;
}

// 指定位置插入
bool
LinkList::Insert(int i, const ElemType &e)
{
  Node *p = new Node(e);
  Node *q = nullptr;

  // 由于设置GetNode时要求1<= parameter <= length
  if (i == 1) {
    p->next = _head->next;
    _head->next = p;
    if (p->next == nullptr)
      _tail = p;
    return true;
  }

  if (p) {
    q = GetNode(i - 1); 
    if (q == nullptr) {
      std::cout << "Insert:: GetNode failed" << std::endl;
      return false;
    }
    else {
      p->next = q->next;
      q->next = p;
      if (p->next == nullptr)
        _tail = p;
    }
  }
  else {
    std::cout << "Insert:: creat node failed" << std::endl;
    return false;
  }
  return true;
}


bool
LinkList::GetElem(int i, ElemType &e)
{

  if (i < 1 || i > GetListLength()) {
    std::cout << "GetElem:: i-> position error" << std::endl;
    return false;
  }

  Node *p = nullptr;
  p = GetNode(i);
  e = p->data;
  return true;
}


bool
LinkList::LocateElem(int &i, const ElemType &e)
{
  Node *p = _head->next;

  i = 0;
  while (p != nullptr) {
    ++i;
    if (p->data != e)
      p = p->next;
    else
      return true;
  }

  if (p == nullptr)
    i = 0;

  return false;
}


bool
LinkList::DeleteNode(int i)
{
  Node *p = nullptr;
  Node *q = nullptr;

  if (i < 1 || i > GetListLength()) {
    std::cout << "DeleteNode(i):: 1 <= i <= length error" << std::endl;
    return false;
  }

  if (i == 1) {
    p = _head->next;
    _head->next = p->next;
    if (p->next == nullptr) { // 只有一个结点
      _tail = _head;
    }
    delete p;
    return true;
  }

  p = GetNode(i - 1);
  q = GetNode(i);
  if (q->next == nullptr)
    _tail = p;
  p->next = q->next;
  delete q;
  return true;
}


void
LinkList::ClearList()
{
  Node *p = nullptr;
  Node *q = nullptr;

  p = _head->next;
  while (p) {
    q = p->next;
    delete p;
    p = q;
  }
  _head->next = nullptr;
  _tail = _head;
}

void
LinkList::PrintList()
{
  Node *p = nullptr;
  for (p = _head->next; p; p = p->next) {
    if (typeid(ElemType) == typeid(int))
      std::cout << p->data << " ";
    else if (typeid(ElemType) == typeid(char))
      std::cout << p->data;
  }
  std::cout << std::endl;
}


bool 
LinkList::isEmpty()
{
  return _head->next == nullptr;
}


int main(void)
{
  LinkList L;
  ElemType e = 0;
  int loc = 0;

  L.HeadInsert('a');
  L.PrintList();
  L.HeadInsert('b');
  L.PrintList();
  L.HeadInsert('c');
  L.PrintList();
  L.HeadInsert('d');
  L.PrintList();
  L.HeadInsert(51);
  L.PrintList();

  std::cout << L << std::endl;

  L.TailInsert('1');
  L.PrintList();
  L.TailInsert('2');
  L.PrintList();
  L.TailInsert('3');
  L.PrintList();

  L.Insert(1, 'a');
  L.PrintList();
  L.Insert(L.GetListLength() + 1, 'w');
  L.PrintList();

  std::cout << "L length: " << L.GetListLength() << std::endl;

  L.DeleteNode(1);
  L.PrintList();
  std::cout << "L length: " << L.GetListLength() << std::endl;
  L.DeleteNode(4);
  L.PrintList();
  std::cout << "L length: " << L.GetListLength() << std::endl;
  L.DeleteNode(0);
  L.PrintList();
  std::cout << "L length: " << L.GetListLength() << std::endl;
  L.DeleteNode(L.GetListLength());
  L.PrintList();
  std::cout << "L length: " << L.GetListLength() << std::endl;

  L.GetElem(1, e);
  std::cout << "链表的第一个结点的数据为：" << e << std::endl;
  L.GetElem(L.GetListLength(), e);
  std::cout << "链表的最后一个结点的数据为：" << e << std::endl;

  L.TailInsert('4');
  L.PrintList();
  L.LocateElem(loc, '4');
  std::cout << "\'4\' 在链表的位置为：" << loc << std::endl;

  std::cout << L << " 这是通过<<运算符重载对链表进行输出" << std::endl;

  return 0;
}
