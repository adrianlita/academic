#pragma once
#include "aNode.h"
#include <iostream>
#include "../utils/utils.h"

/*
sLinkedList definition. implementation is below because it needs to reside within the h file

template <typename Type>
class sLinkedList
{
  sNode<Type> *head;
  sNode<Type> *tail;
  unsigned int length;
public:
  sLinkedList();
  sLinkedList(const sLinkedList<Type>& rhs);
  ~sLinkedList();

  sLinkedList<Type>& operator=(const sLinkedList<Type>& rhs);

  void Add_List_To_Tail(const sLinkedList<Type>& list);                                       //copyies list to the tail of current list

  //element add/remove/search
  void Add_To_Head(const Type& element);                                                      //adds *new* element to the head of current list. very efficient
  void Add_To_Tail(const Type& element);                                                      //adds *new* element to the tail of current list. very efficient
  void Add_To_Position(const Type& element, const unsigned int pos);                          //adds *new* element to a certain position of current list. pretty efficient. if pos is greater than length, it will be added to the tail

  sLinkedList<Type> operator+(const Type& element);                                           //returns *new* list which has element added to the tail. not recommended, as inefficient
  friend sLinkedList<Type> operator+(const Type& element, const sLinkedList<Type>& list);     //returns *new* list which has element added to the head. not recommended, as inefficient
  sLinkedList<Type> operator+(const sLinkedList<Type>& list);                                 //returns *new* list which has list copied to the tail. not recommended, as inefficient

  sLinkedList<Type>& operator+=(const Type& rhs);                                             //adds *new* element to the tail of current list. efficient
  sLinkedList<Type>& operator+=(const sLinkedList<Type>& rhs);                                //copies *new* list to the tail of current list. efficient

  bool Remove_Head();                                                                         //removes first element if exists and returns true. returns false if list had no elements. very efficient
  bool Remove_Tail();                                                                         //removes last element if exists and returns true. returns false if list had no elements. highly inefficient
  bool Remove_All();                                                                          //removes all elements from list if exists and returns true. returns false if list had no elements
  bool Remove_First_Found(const Type& element);                                               //removes first element that matches the paramter if exists and returns true. returns false if list had no elements or element is not found
  bool Remove_From_Position(const unsigned int pos);                                          //removes element from position pos if exists and returns true. returns false if list had less than pos elements

  unsigned int Length() const;                                                                //returns the total number of elements
  Type& operator[](const unsigned int index);                                                 //returns list as a vector, with its respective element. throws error if index is larger than the list size

  bool Exists(const Type& element) const;                                                     //returns the true if element exists, false if not
  aListSearchResult Search(const Type& element) const;                                        //searches for element. if no element is found, will update the return structure accordingly

  friend std::ostream& operator<<(std::ostream& out, const sLinkedList<Type>& rhs);
};

*/

template <typename Type>
class sLinkedList
{
  sNode<Type> *head;
  sNode<Type> *tail;
  unsigned int length;
public:
  unsigned int Length() const
  {
    return length;
  }

  //element add/remove/search
  void Add_To_Head(const Type& element)
  {
    sNode<Type> *p = new sNode<Type>(element);
    check_if_allocated_correctly(p);
    p->next = head->next;
    head->next = p;
    if(head == tail)
      tail = p;
    length++;
  }

  void Add_To_Tail(const Type& element)
  {
    sNode<Type> *p = new sNode<Type>(element);
    check_if_allocated_correctly(p);
    tail->next = p;
    tail = p;
    length++;
  }

  void Add_To_Position(const Type& element, const unsigned int pos)
  {  
    if((pos == 0) || (length == 0))
      Add_To_Head(element);
    else
    if(pos >= length)
      Add_To_Tail(element);
    else
    {
      unsigned int i = 0;
      sNode<Type> *crt = head;
      sNode<Type> *p = new sNode<Type>(element);

      while(i < pos)
      {
        crt = crt->next;
        i++;
      }

      p->next = crt->next;
      crt->next = p;
      length++;
    }
  }

  bool Remove_Head()
  {
    if(!head->next)
      return false;

    sNode<Type> *p = head->next;
    head->next = p->next;

    if(p == tail)
      tail = head;

    delete p;
    length--;

    return true;
  }

  bool Remove_Tail()
  {
    if(!head->next)
      return false;

    sNode<Type> *p = head;
    while(p->next != tail)
      p = p->next;;

    delete p->next;
    length--;
    p->next = NULL;

    if(p == head)
      tail = head;
    else
      tail = p;

    return true;
  }

  bool Remove_All()
  {
    if(!head->next)
      return false;

    sNode<Type> *p = head->next;
    while(p)
    {
      sNode<Type> *s = p;
      p = p->next;
      delete s;
    }

    length = 0;
    head->next = NULL;
    tail = head;

    return true;
  }

  bool Remove_First_Found(const Type& element)
  { 
    sNode<Type> *crt = head;

    while(crt->next)
    {
      if(crt->next->data == element)
      {
        sNode<Type> *p = crt->next;
        crt->next = p->next;
        delete p;
        if(p == tail)
          tail = crt;
        length--;
        return true;
      }

      crt = crt->next;
    }
  
    return false; //not found
  }

  bool Remove_From_Position(const unsigned int pos)
  {
    if(pos >= length)
      return false;

    if(pos == 0)
      return Remove_Head();
    else
    {
      unsigned int i = 0;
      sNode<Type> *crt = head;

      while(i < pos)
      {
        crt = crt->next;
        i++;
      }

      sNode<Type> *p = crt->next;
      crt->next = p->next;
      delete p;
      if(p == tail)
        tail = crt;
      length--;
    }

    return true;
  }

  void Add_List_To_Tail(const sLinkedList<Type>& list)
  {
    sNode<Type> *crt = list.head->next;
    while(crt)
    {
      Add_To_Tail(crt->data);
      crt = crt->next;
    }
  }

  sLinkedList()
  {
    length = 0;
    head = new sNode<Type>;
    check_if_allocated_correctly(head);
    tail = head;
  }

  sLinkedList(const sLinkedList<Type>& rhs)
  {
    length = 0;
    head = new sNode<Type>;
    check_if_allocated_correctly(head);
    tail = head;
    
    Add_List_To_Tail(rhs);
  }

  ~sLinkedList()
  {
    Remove_All();
    delete head;
  }

  sLinkedList<Type>& operator=(const sLinkedList<Type>& rhs)
  {
    if(this != &rhs)
    {
      Remove_All();
      Add_List_To_Tail(rhs);
    }
    return *this;
  }

  
  sLinkedList<Type> operator+(const Type& element)
  {
    sLinkedList<Type> result = *this;
    result.Add_To_Tail(element);
    return result;
  }

  friend sLinkedList<Type> operator+(const Type& element, const sLinkedList<Type>& list)
  {
    sLinkedList<Type> result = list;
    result.Add_To_Head(element);
    return result;
  }

  sLinkedList<Type> operator+(const sLinkedList<Type>& list)
  {
    sLinkedList<Type> result = *this;
    result.Add_List_To_Tail(list);
    return result;
  }


  sLinkedList<Type>& operator+=(const Type& rhs)
  {
    Add_To_Tail(rhs);
    return *this;
  }

  sLinkedList<Type>& operator+=(const sLinkedList<Type>& rhs)
  {
    Add_List_To_Tail(rhs);
    return *this;
  }

  Type& operator[](const unsigned int index)
  {
    if(index >= length)
      throw "index is out of bounds";

    unsigned int i = 0;
    sNode<Type> *p = head->next;

    while(i < index)
    {
      p = p->next;
      i++;
    }
    return p->data;
  }

  bool Exists(const Type& element) const
  {
    sNode<Type> *p = head->next;
    while(p)
    {
      if(p->data == element)
        return true;
      p = p->next;
    }
    return false;
  }

  aListSearchResult Search(const Type& element) const
  {
    aListSearchResult result;
    unsigned int i = 0;
    
    result.found = false;

    sNode<Type> *p = head->next;
    while(p)
    {
      if(p->data == element)
      {
        result.position = i;
        result.found = true;
        return result;
      }

      p = p->next;
      i++;
    }

    return result;
  }

  friend std::ostream& operator<<(std::ostream& out, const sLinkedList<Type>& rhs)
  {
    sNode<Type> *crt = rhs.head->next;
    if(crt)
    {
      while(crt->next)
      {
        out << crt->data << ", ";
        crt = crt->next;
      }
      out << crt->data;
    }
    return out;
  }
};
