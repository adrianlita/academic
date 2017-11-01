#pragma once
#include "aNode.h"
#include <iostream>
#include "../utils/utils.h"

/*
dLinkedList definition. implementation is below because it needs to reside within the h file

template <typename Type>
class dLinkedList
{
  dNode<Type> *head;
  dNode<Type> *tail;
  unsigned int length;
  bool direction;   //run direction for ostream&

  dNode<Type> *current;
  unsigned int current_position;
public:
  dLinkedList();
  dLinkedList(const dLinkedList<Type>& rhs);
  ~dLinkedList();

  dLinkedList<Type>& operator=(const dLinkedList<Type>& rhs);

  void Add_List_To_Tail(const dLinkedList<Type>& list);                                       //copyies list to the tail of current list

  //element add/remove/search
  void Add_To_Head(const Type& element);                                                      //adds *new* element to the head of current list. very efficient
  void Add_To_Tail(const Type& element);                                                      //adds *new* element to the tail of current list. very efficient
  void Add_To_Position(const Type& element, const unsigned int pos);                          //adds *new* element to a certain position of current list. pretty efficient. if pos is greater than length, it will be added to the tail

  dLinkedList<Type> operator+(const Type& element);                                           //returns *new* list which has element added to the tail. not recommended, as inefficient
  friend dLinkedList<Type> operator+(const Type& element, const dLinkedList<Type>& list);     //returns *new* list which has element added to the head. not recommended, as inefficient
  dLinkedList<Type> operator+(const dLinkedList<Type>& list);                                 //returns *new* list which has list copied to the tail. not recommended, as inefficient

  dLinkedList<Type>& operator+=(const Type& rhs);                                             //adds *new* element to the tail of current list. efficient
  dLinkedList<Type>& operator+=(const dLinkedList<Type>& rhs);                                //copies *new* list to the tail of current list. efficient

  bool Remove_Head();                                                                         //removes first element if exists and returns true. returns false if list had no elements. very efficient
  bool Remove_Tail();                                                                         //removes last element if exists and returns true. returns false if list had no elements. very efficient
  bool Remove_All();                                                                          //removes all elements from list if exists and returns true. returns false if list had no elements. very efficient
  bool Remove_From_Position(const unsigned int pos);                                          //removes element from position pos if exists and returns true. returns false if list had less than pos elements. improved efficiency

  unsigned int Length() const;                                                                //returns the total number of elements
  Type& operator[](const unsigned int index) const;                                           //returns list as a vector, with its respective element. throws error if index is larger than the list size

  bool Exists(const Type& element) const;                                                     //returns the true if element exists, false if not
  aListSearchResult Search_From_Head(const Type& element) const;                              //searches for element starting from head. if no element is found, will update the return structure accordingly
  aListSearchResult Search_From_Tail(const Type& element) const;                              //searches for element starting from tail. if no element is found, will update the return structure accordingly

  bool Set_Current_Element_Position(unsigned int pos);                                        //sets current element position, and if successful, returns true. if list is empty or pos is larger than size, it will return false
  unsigned int Get_Current_Element_Position();                                                //gets current element position. if list is empty, will throw error
  Type& Current_Element();                                                                    //returns bidirectional access to current element data. if current element is not set, will throw error

  dLinkedList<Type>& operator++();                                                            //advances current element forward (next)
  dLinkedList<Type>& operator--();                                                            //advances current element backward (prev)

  friend std::ostream& operator<<(std::ostream& out, const dLinkedList<Type>& rhs);
};
*/


template <typename Type>
class dLinkedList
{
  dNode<Type> *head;
  dNode<Type> *tail;
  unsigned int length;
  bool direction;

  dNode<Type> *current;
  unsigned int current_position;
public:
  unsigned int Length() const
  {
    return length;
  }

  //element add/remove/search
  void Add_To_Head(const Type& element)
  {
    dNode<Type> *p = new dNode<Type>(element);
    check_if_allocated_correctly(p);
    p->next = head->next;
    p->prev = head;
    head->next->prev = p;
    head->next = p;
    if(head == tail)
      tail = p;
    length++;
  }

  void Add_To_Tail(const Type& element)
  {
    dNode<Type> *p = new dNode<Type>(element);
    check_if_allocated_correctly(p);
    tail->next = p;
    p->prev = tail;
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
      if(pos < length/2)
      {
        //go head->tail
        unsigned int i = 0;
        dNode<Type> *crt = head;
        dNode<Type> *p = new dNode<Type>(element);

        while(i < pos)
        {
          crt = crt->next;
          i++;
        }

        p->next = crt->next;
        crt->next->prev = p;
        crt->next = p;
        p->prev = crt;
        length++;
      }
      else
      {
        //go tail->head
        unsigned int i = length - 1;
        dNode<Type> *crt = tail;
        dNode<Type> *p = new dNode<Type>(element);

        while(i > pos)
        {
          crt = crt->prev;
          i--;
        }

        p->prev = crt->prev;
        crt->prev->next = p;
        crt->prev = p;
        p->next = crt;
        length++;
      }
    }
  }


  bool Remove_Head()
  {
    if(!head->next)
      return false;

    dNode<Type> *p = head->next;
    head->next = p->next;
    head->next->prev = head;

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

    dNode<Type> *p = tail;
    tail->prev->next = NULL;
    tail = tail->prev;

    delete p;
    length--;

    return true;
  }
  
  bool Remove_All()
  {
    if(!head->next)
      return false;

    dNode<Type> *p = head->next;
    while(p)
    {
      dNode<Type> *s = p;
      p = p->next;
      delete s;
    }

    length = 0;
    head->next = NULL;
    tail = head;

    return true;
  }

  bool Remove_From_Position(const unsigned int pos)
  {
    if(pos >= length)
      return false;

    if(pos == 0)
      return Remove_Head();
    else
    {
      if(pos < length/2)
      {
        //go head->tail
        unsigned int i = 0;
        dNode<Type> *crt = head;

        while(i < pos)
        {
          crt = crt->next;
          i++;
        }

        dNode<Type> *p = crt->next;
        crt->next = p->next;
        crt->next->prev = crt;
        delete p;
        if(p == tail)
          tail = crt;
        length--;
      }
      else
      {
        //go tail->head
        unsigned int i = length - 1;
        dNode<Type> *crt = tail;

        while(i > pos)
        {
          crt = crt->prev;
          i--;
        }

        dNode<Type> *p = crt->prev;
        crt->prev = p->prev;
        crt->prev->next = crt;
        delete p;
        if(p == tail)
          tail = crt;
        length--;
      }
    }

    return true;
  }

  void Add_List_To_Tail(const dLinkedList<Type>& list)
  {
    dNode<Type> *crt = list.head->next;
    while(crt)
    {
      Add_To_Tail(crt->data);
      crt = crt->next;
    }
  }

  dLinkedList()
  {
    length = 0;
    head = new dNode<Type>;
    check_if_allocated_correctly(head);
    tail = head;
    direction = false;
  }

  dLinkedList(const dLinkedList<Type>& rhs)
  {
    length = 0;
    head = new dNode<Type>;
    check_if_allocated_correctly(head);
    tail = head;
    direction = false;

    Add_List_To_Tail(rhs);
  }

  ~dLinkedList()
  {
    Remove_All();
    delete head;
  }

  dLinkedList<Type>& operator=(const dLinkedList<Type>& rhs)
  {
    if(this != &rhs)
    {
      Remove_All();
      direction = rhs.direction;
      Add_List_To_Tail(rhs);
    }
    return *this;
  }

  dLinkedList<Type> operator+(const Type& element)
  {
    dLinkedList<Type> result = *this;
    result.Add_To_Tail(element);
    return result;
  }

  friend dLinkedList<Type> operator+(const Type& element, const dLinkedList<Type>& list)
  {
    dLinkedList<Type> result = list;
    result.Add_To_Head(element);
    return result;
  }

  dLinkedList<Type> operator+(const dLinkedList<Type>& list)
  {
    dLinkedList<Type> result = *this;
    result.Add_List_To_Tail(list);
    return result;
  }


  dLinkedList<Type>& operator+=(const Type& rhs)
  {
    Add_To_Tail(rhs);
    return *this;
  }

  dLinkedList<Type>& operator+=(const dLinkedList<Type>& rhs)
  {
    Add_List_To_Tail(rhs);
    return *this; 
  }


  Type& operator[](const unsigned int index)
  {
    static Type trash;
    return trash;
  }

  aListSearchResult Search_From_Head(const Type& element) const
  {
    aListSearchResult result;
    unsigned int i = 0;
    
    result.found = false;

    dNode<Type> *p = head->next;
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

  aListSearchResult Search_From_Tail(const Type& element) const
  {
    aListSearchResult result;
    unsigned int i = length - 1;
    
    result.found = false;

    dNode<Type> *p = tail;
    while((p != head) && p)
    {
      if(p->data == element)
      {
        result.position = i;
        result.found = true;
        return result;
      }

      p = p->prev;
      i--;
    }

    return result;
  }

  // bool Set_Current_Element_Position(unsigned int pos);
  // unsigned int Get_Current_Element_Position();
  // Type& Current_Element();

  // dLinkedList<Type>& operator++();
  // dLinkedList<Type>& operator--();

  void Set_Run_Direction(bool tail_to_head)
  {
    direction = tail_to_head;
  }

  friend std::ostream& operator<<(std::ostream& out, const dLinkedList<Type>& rhs)
  {
    bool direction = rhs.direction;
    if(direction == false)
    {
      dNode<Type> *crt = rhs.head->next;
      if(crt)
      {
        while(crt->next)
        {
          out << crt->data << ", ";
          crt = crt->next;
        }
        out << crt->data;
      }
    }
    else
    {
      dNode<Type> *crt = rhs.tail;
      if(crt != rhs.head)
      {
        while(crt->prev != rhs.head)
        {
          out << crt->data << ", ";
          crt = crt->prev;
        }
        out << crt->data;
      }
    }
    return out;
  }
};
