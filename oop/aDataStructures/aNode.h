#pragma once

#include <iostream>

//forward declarations. otherwise we can't make them friend classes
template <typename Type> class sLinkedList;
template <typename Type> class aStack;
template <typename Type> class aQueue;
template <typename Type> class dLinkedList;
template <typename Type> class aBinarySearchTree;
template <typename Type> class aAVLTree;


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
protected:
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
  
  friend class aBinarySearchTree<Type>;
  friend class aAVLTree<Type>;
};

//tNodeAVL - node implementation for AVL trees
template <typename Type>
class tNodeAVL : public tNode<Type>
{
  int balance;

  int height(const tNodeAVL<Type>* node)
  {
    if(!node)
		  return 0;

    int leftHeight = height((tNodeAVL<Type>*)(node->left));
    int rightHeight = height((tNodeAVL<Type>*)(node->right));
    
    if(leftHeight > rightHeight)
      return leftHeight + 1;
    else
      return rightHeight + 1;
  }

  void calculate_balance()
  {
    balance = height((tNodeAVL<Type>*)(this->right)) - height((tNodeAVL<Type>*)(this->left));
  } 
public:
  tNodeAVL() : tNode<Type>()
  {
    balance = 0;
  }
  
  tNodeAVL(const Type& value) : tNode<Type>(value)
  {
    balance = 0;
  }
  
  friend class aAVLTree<Type>;
};

//result for searching in lists
struct aListSearchResult
{
  bool found;
  unsigned int position;
};
