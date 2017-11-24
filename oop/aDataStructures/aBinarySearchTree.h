#pragma once
#include "aNode.h"
#include <iostream>
#include "../utils/utils.h"

/*
aBinarySearchTree definition. implementation is below because it needs to reside within the h file


template <typename Type>
class aBinarySearchTree
{
protected:
  tNode<Type> *root;

  void pre_order(const tNode<Type>* node) const;
  void in_order(const tNode<Type>* node) const;
  void post_order(const tNode<Type>* node) const;

  virtual tNode<Type>* delete_element(tNode<Type>* node, const Type& element, bool& found);
  bool element_exists(const tNode<Type> *node, const Type& element) const;
  unsigned int count_nodes(const tNode<Type> *node) const;

  void delete_tree(const tNode<Type> *node);
  void copy_tree(tNode<Type> *root_dest, const tNode<Type> *root_source);
  void output(std::ostream& out, const tNode<Type> *node) const;
public:
  aBinarySearchTree();
  aBinarySearchTree(const aBinarySearchTree<Type>& rhs);
  virtual ~aBinarySearchTree();
  aBinarySearchTree<Type>& operator=(const aBinarySearchTree<Type>& rhs);

  unsigned int Total_Nodes() const;                                                           //returns the total number of nodes

  bool Exists(const Type& element) const;                                                     //returns the true if element exists, false if not

  virtual void Add(const Type& element);                                                      //adds element to BST
  virtual bool Delete(const Type& element);                                                   //tries to remove element to BST. returns true if element existed, false if not

  void PreOrder() const;                                                                      //parses the tree in preorder (Root Left Right)
  void InOrder() const;                                                                       //parses the tree in order (Left Root Right)
  void PostOrder() const;                                                                     //parses the tree in post order (Right Root Left)
  
  friend std::ostream& operator<<(std::ostream& out, const aBinarySearchTree<Type>& rhs);
};

*/


template <typename Type>
class aBinarySearchTree
{
protected:
  tNode<Type> *root;

  void pre_order(const tNode<Type>* node) const
  {
    if(node == NULL)
      return;

    std::cout << node->data << " ";
    pre_order(node->left);
    pre_order(node->right);
  }

  void in_order(const tNode<Type>* node) const
  {
    if(node == NULL)
      return;

    in_order(node->left);
    std::cout << node->data << " ";
    in_order(node->right);
  }

  void post_order(const tNode<Type>* node) const
  {
    if(node == NULL)
      return;

    post_order(node->right);
    std::cout << node->data << " ";
    post_order(node->left);
  }


  virtual tNode<Type>* delete_element(tNode<Type>* node, const Type& element, bool& found)
  {
    if(node == NULL)
      return NULL;

    if(element < node->data)
      node->left = delete_element(node->left, element, found);
    else
    if(element > node->data)
      node->right = delete_element(node->right, element, found);
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
    if(root_source == NULL)
      return;
    
    if(root_source->left)
    {
      root_dest->left = new tNode<Type>(root_source->left->data);
      copy_tree(root_dest->left, root_source->left);
    }

    if(root_source->right)
    {
      root_dest->right = new tNode<Type>(root_source->right->data);
      copy_tree(root_dest->right, root_source->right);
    }
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
    if(rhs.root)
    {
      root = new tNode<Type>(rhs.root->data);
      copy_tree(root, rhs.root);
    }
  }

  virtual ~aBinarySearchTree()
  {
    delete_tree(root);
  }

  aBinarySearchTree<Type>& operator=(const aBinarySearchTree<Type>& rhs)
  {
    if(this != &rhs)
    {
      delete_tree(root);
      root = NULL;
      if(rhs.root)
      {
        root = new tNode<Type>(rhs.root->data);
        copy_tree(root, rhs.root);
      }
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

  virtual void Add(const Type& element)
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

  virtual bool Delete(const Type& element)
  {
    if(root == NULL)
      return false;

    bool found;
    found = false;

    root = delete_element(root, element, found);
    return found;
  }

  void PreOrder() const
  {
    pre_order(root);
    std::cout << std::endl;
  }

  void InOrder() const
  {
    in_order(root);
    std::cout << std::endl;
  }

  void PostOrder() const
  {
    post_order(root);
    std::cout << std::endl;
  }

  friend std::ostream& operator<<(std::ostream& out, const aBinarySearchTree<Type>& rhs)
  {
    rhs.output(out, rhs.root);
    return out;
  }

};
