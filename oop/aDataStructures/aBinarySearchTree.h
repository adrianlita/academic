#pragma once
#include "aNode.h"
#include <iostream>
#include "../utils/utils.h"

/*
aBinarySearchTree definition. implementation is below because it needs to reside within the h file

template <typename Type>
class aBinarySearchTree
{
  tNode<Type> *root;

  bool element_exists(const tNode<Type> *node, const Type& element) const;
  unsigned int count_nodes(const tNode<Type> *node) const;
  void delete_tree(const tNode<Type> *node);
  void copy_tree(tNode<Type> *root_dest, const tNode<Type> *root_source);

  void output(std::ostream& out, const tNode<Type> *node) const;
public:
  aBinarySearchTree();
  aBinarySearchTree(const aBinarySearchTree<Type>& rhs);
  ~aBinarySearchTree();
  aBinarySearchTree<Type>& operator=(const aBinarySearchTree<Type>& rhs);

  unsigned int Total_Nodes() const;                                                           //returns the total number of nodes

  bool Exists(const Type& element) const;                                                     //returns the true if element exists, false if not

  void Add(const Type& element);                                                              //adds element to BST
  bool Remove(const Type& element);                                                           //tries to remove element to BST. returns true if element existed, false if not
  
  friend std::ostream& operator<<(std::ostream& out, const aBinarySearchTree<Type>& rhs);
};

*/


template <typename Type>
class aBinarySearchTree
{
protected:
  tNode<Type> *root;

  bool element_exists(const tNode<Type> *node, const Type& element) const
  {
    if(!node)
      return false;

    if(element == node->data)
      return true;
    else
      return (element_exists(node->left, element) || element_exists(node->right, element));
  }

  unsigned int count_nodes(const tNode<Type> *node) const
  {
    if(!node)
      return 0;

    return 1+count_nodes(node->left) + count_nodes(node->right);
  }

  void delete_tree(const tNode<Type> *node)
  {
    if(node)
    {
      delete_tree(node->left);
      delete_tree(node->right);
      delete node;
    }
  }

  void copy_tree(tNode<Type> *root_dest, const tNode<Type> *root_source)
  {
    
  }

  void output(std::ostream& out, const tNode<Type> *node) const
  {
    if(!node)
    {
      out << "-";
      return;
    }

    out << node->data;
    if(node->left || node->right)
    {
      out << "(";
      output(out, node->left);
      out << ",";
      output(out, node->right);
      out << ")";
    }
  }
public:
  aBinarySearchTree()
  {
    root = NULL;
  }

  aBinarySearchTree(const aBinarySearchTree<Type>& rhs)
  {
    root = NULL;
  }

  ~aBinarySearchTree()
  {
    delete_tree(root);
  }

  aBinarySearchTree<Type>& operator=(const aBinarySearchTree<Type>& rhs)
  {
    if(this != &rhs)
    {
      delete_tree(root);
      copy_tree(root, rhs.root);
    }
    return *this;
  }


  unsigned int Total_Nodes() const
  {
    return count_nodes(root);
  }


  bool Exists(const Type& element) const
  {
    return element_exists(root, element);
  }

  
  void Add(const Type& element)
  {
    if(root == NULL)
    {
      root = new tNode<Type>(element);
      check_if_allocated_correctly(root);
      return;
    }

    tNode<Type> *node = root;
    while(node)
    {
      if(element < node->data)
        if(node->left)
          node = node->left;
        else
        {
          node->left = new tNode<Type>(element);
          check_if_allocated_correctly(node->left);
          return;
        }
      else
        if(node->right)
          node = node->right;
        else
        {
          node->right = new tNode<Type>(element);
          check_if_allocated_correctly(node->right);
          return;
        }
    }
  }

  bool Remove(const Type& element)
  {

  }

  
  friend std::ostream& operator<<(std::ostream& out, const aBinarySearchTree<Type>& rhs)
  {
    rhs.output(out, rhs.root);
    return out;
  }

};
