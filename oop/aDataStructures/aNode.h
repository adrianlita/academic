#pragma once

#include <iostream>

//forward declarations. otherwise we can't make them friend classes
template <typename Type> class sLinkedList;
template <typename Type> class aStack;
template <typename Type> class aQueue;
template <typename Type> class dLinkedList;
template <typename Type> class aBinaryTree;


//sNode - node implementation for simple linked list, queue and stack
template <typename Type>
class sNode
{
  Type data;
  sNode* next;
public:
  sNode()
  {
    next = NULL;
  }

  sNode(const Type& value)
  {
    data = value;
    next = NULL;
  }

  friend class sLinkedList<Type>;
  friend class aStack<Type>;
  friend class aQueue<Type>;
};

//dNode - node implementation for double linked list
template <typename Type>
class dNode
{
  Type data;
  dNode* prev;
  dNode* next;
public:
  dNode()
  {
    prev = NULL;
    next = NULL;
  }
  dNode(const Type& value)
  {
    data = value;
    prev = NULL;
    next = NULL;
  }

  friend class dLinkedList<Type>;
};

//tNode - node implementation for binary trees
template <typename Type>
class tNode
{
  Type data;
  tNode* left;
  tNode* right;
public:
  tNode()
  {
    left = NULL;
    right = NULL;
  }
  
  tNode(const Type& value)
  {
    data = value;
    left = NULL;
    right = NULL;
  }
  
  friend class aBinaryTree<Type>;
};

//result for searching in lists
struct aListSearchResult
{
  bool found;
  unsigned int position;
};
