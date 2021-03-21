#ifndef __BINARY_SEARCH_TREE__
#define __BINARY_SEARCH_TREE__

#include <iostream>

template<class T>
// 树结点结构
class BSTNode {
public:
  T _key;
  BSTNode *_lchild;
  BSTNode *_rchild;
  BSTNode *_parent;

  BSTNode(T key, BSTNode *lchild, BSTNode *rchild, BSTNode *parent)
    : _key(key), _lchild(lchild), _rchild(rchild), _parent(parent)
  { }
};

template<typename T>
class BSTree {
private:
  BSTNode<T> *_Root;  // 根节点

public:
  BSTree() : _Root(nullptr) { }
  ~BSTree();

  void insert(T key);

  BSTNode<T>* search(T key);

  void preOrder();
  void inOrder();
  void postOrder();

  BSTNode<T>* minimumNode();  // 查找最小的结点
  BSTNode<T>* maximumNode();  // 查找最大的结点

  T minimunKey();             // 查找最小的键值
  T maximumKey();             // 查找最大的键值

  void print();               // 打印二叉树
  void remove();              // 移除某个结点

  // 查找某个结点的前驱，树中所有数取出之后排序从小到大排序，靠近x左边的数
  BSTNode<T>* predecessor(BSTNode<T> *x);
  // 查找某个结点的后继，树中所有数取出之后排序从小到大排序，靠近x右边的数
  BSTNode<T>* sucessor(BSTNode<T> *x);

  void destroy();

private:
  void insert(BSTNode<T>* &tree, BSTNode<T>* z);

};




#endif
