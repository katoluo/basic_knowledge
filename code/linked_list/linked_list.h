#ifndef __LINKED_LIST__
#define __LINKED_LIST__
#include <iostream>

typedef char ElemType;
struct Node {
  ElemType data;
  struct Node *prior;
  struct Node *next;
  Node() = default;
  Node(ElemType e) : data(e), prior(nullptr), next(nullptr) { }
};
class LinkList;
std::ostream&
operator<< (std::ostream &os, const LinkList &L);

class LinkList {
  friend std::ostream& operator<< (std::ostream &os, const LinkList &L);
public:
  LinkList();
  LinkList(const LinkList&) = delete;
  LinkList& operator= (const LinkList&) = delete;
  ~LinkList();

  // 基本操作
  bool HeadInsert(const ElemType &e);  // 头插
  bool TailInsert(const ElemType &e);  // 尾插
  bool Insert(int i, const ElemType &e);  // 指定位置插入
  bool GetElem(int i, ElemType &e);  // 按序号查找结点值
  bool LocateElem(int &i, const ElemType &e);  // 按值查找表结点
  bool DeleteNode(int i);        // 按序号删除结点
  int GetListLength();           // 获取表长
  void ClearList();  // 删除除头结点外的所有结点
  // 其他操作
  void PrintList();  // 打印整个链表

private:
  bool CreatList();
  void DestroyList();
  Node* GetNode(int i);
  bool isEmpty();

private:
  Node *_head;
  Node *_tail;
};


#endif

