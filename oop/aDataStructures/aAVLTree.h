#pragma once
#include "aNode.h"
#include "aBinarySearchTree.h"
#include <iostream>
#include "../utils/utils.h"

/*
aAVLTree definition. implementation is below because it needs to reside within the h file

template <typename Type>
class aAVLTree : public aBinarySearchTree<Type>
{
  //NOTE: root is defined in base class as tNode<Type>*, but in this tree, we create tNodeAVL<Type> objects in it (polymorphism)

  tNode<Type>* LeftRotateS(tNode<Type>* node);
  tNode<Type>* RightRotateS(tNode<Type>* node);
  tNode<Type>* LeftRotateD(tNode<Type>* node);
  tNode<Type>* RightRotateD(tNode<Type>* node);
 
  tNode<Type>* rebalance(tNode<Type>* node);
  tNode<Type>* add_element(tNode<Type>* node, const Type& element);
  void copy_tree(const tNode<Type> *root_source);

  INHERITED:
  tNode<Type> *root;

  void pre_order(const tNode<Type>* node) const;
  void in_order(const tNode<Type>* node) const;
  void post_order(const tNode<Type>* node) const;

  bool element_exists(const tNode<Type> *node, const Type& element) const;
  unsigned int count_nodes(const tNode<Type> *node) const;

  void delete_tree(const tNode<Type> *node);
  void output(std::ostream& out, const tNode<Type> *node) const;

  INHERITED AND OVERLOADED:
  void copy_tree(tNode<Type> *root_dest, const tNode<Type> *root_source); //we don't want to use this, we defined or own
  tNode<Type>* delete_element(tNode<Type>* node, const Type& element, bool& found); //we also want to rebalance 

public:
  aAVLTree() : aBinarySearchTree<Type>();
  aAVLTree(const aAVLTree<Type>& rhs);
  aAVLTree<Type>& operator=(const aAVLTree<Type>& rhs);
  
  void Add(const Type& element);
  bool Delete(const Type& element);

  INHERITED:
  ~aBinarySearchTree();
  unsigned int Total_Nodes() const;
  bool Exists(const Type& element) const;

  void PreOrder() const;
  void InOrder() const;
  void PostOrder() const;
  
  friend std::ostream& operator<<(std::ostream& out, const aBinarySearchTree<Type>& rhs);
};

*/

template <typename Type>
class aAVLTree : public aBinarySearchTree<Type>
{
  static void copy_tree(tNode<Type> *root_dest, const tNode<Type> *root_source);

  tNode<Type>* LeftRotateS(tNode<Type>* node)
  {
    tNode<Type>* temp;
    temp = node->right;
    node->right = temp->left;
    temp->left = node;
    ((tNodeAVL<Type>*)node)->calculate_balance();
    ((tNodeAVL<Type>*)temp)->calculate_balance();
    node = temp;
    return node;
  }

  tNode<Type>* RightRotateS(tNode<Type>* node)
  {
    tNode<Type>* temp;
    temp = node->left;
    node->left = temp->right;
    temp->right = node;
    ((tNodeAVL<Type>*)node)->calculate_balance();
    ((tNodeAVL<Type>*)temp)->calculate_balance();
    node = temp;
    return node;
  }

  tNode<Type>* LeftRotateD(tNode<Type>* node)
  {
    node->right = RightRotateS(node->right);
    node = LeftRotateS(node);
    return node;
  }

  tNode<Type>* RightRotateD(tNode<Type>* node)
  {
    node->left = LeftRotateS(node->left);
    node = RightRotateS(node);
    return node;
  }

  tNode<Type>* rebalance(tNode<Type>* node)
  {
    tNode<Type>* temp;
    ((tNodeAVL<Type>*)node)->calculate_balance();
    if(((tNodeAVL<Type>*)node)->balance == -2)
    {
      temp = node->left;
      if (((tNodeAVL<Type>*)temp)->balance == 1)
        node = RightRotateD(node);
      else
        node = RightRotateS(node);
    }
    else
    if(((tNodeAVL<Type>*)node)->balance == 2)
    {
      temp = node->right;
      if (((tNodeAVL<Type>*)temp)->balance == -1)
        node = LeftRotateD(node);
      else
        node = LeftRotateS(node);
    }
    return node;
  }


  tNode<Type>* delete_element(tNode<Type>* node, const Type& element, bool& found)
  {
    if(node == NULL)
      return NULL;

    if(element < node->data)
    {
      node->left = delete_element(node->left, element, found);
      node = rebalance(node);
    }
    else
    if(element > node->data)
    {
      node->right = delete_element(node->right, element, found);
      node = rebalance(node);
    }
    else
    {
      if(node->left == NULL && node->right == NULL)
      {
        delete node;
        found = true;
        node = NULL;
      }
      
      else
      if(node->left == NULL)
      {
        tNode<Type> *temp = node;
        node = node->right;
        delete temp;
        found = true;
      }
      
      else
      if(node->right == NULL)
      {
        tNode<Type> *temp = node;
        node = node->left;
        delete temp;
        found = true;
      }
      else
      {
        tNode<Type> *temp = node->right;
        while(temp->left)
          temp = temp->left;

        node->data = temp->data;  //it's easier to interchange elements in between than to change children, etc
        node->right = delete_element(node->right, temp->data, found);
      }
    }

    return node; // parent node can update reference
  }

  tNode<Type>* add_element(tNode<Type>* node, const Type& element)
  {
    if(!node)
    {
      tNode<Type>* e = new tNodeAVL<Type>(element);
      check_if_allocated_correctly(e);
      return e;
    }
    
    if(element < node->data)
      node->left = add_element(node->left, element);
    else
    if(element > node->data)
      node->right = add_element(node->right, element);
    else
      std::cout<<"Informatia deja exista!"<<std::endl;
      
    node = rebalance(node);
    return node;
  }

  void copy_tree(const tNode<Type> *root_source)
  {
    if(root_source == NULL)
      return;
    
    Add(root_source->data);
    copy_tree(root_source->left);
    copy_tree(root_source->right);
  }

public:
  aAVLTree() : aBinarySearchTree<Type>()
  {
  }

  aAVLTree(const aAVLTree<Type>& rhs)
  {
    this->root = NULL;
    copy_tree(rhs.root);
  }

  aAVLTree<Type>& operator=(const aAVLTree<Type>& rhs)
  {
    if(this != &rhs)
    {
      delete_tree(this->root);
      this->root = NULL;
      if(rhs.root)
        copy_tree(rhs.root);
    }
    return *this;
  }

  void Add(const Type& element)
  {
    this->root = add_element(this->root, element);
  }

  bool Delete(const Type& element)
  {
    if(this->root == NULL)
      return false;

    bool found;
    found = false;

    this->root = delete_element(this->root, element, found);
    return found;
  }
};
