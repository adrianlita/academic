#pragma once

#include "aNode.h"
#include "sLinkedList.h"

/*
aInheritedStack definition:
  - Last In First Out (LIFO)
  - a stack which is derived from a simply linked list
  - implementation is below because the use of templates

aStack definition:
  - stack (LIFO) implementation. basically strip off everything not needed from list
  - does not inherit anything
  - does not use sentinel element as sLinkedList

template <typename Type>
class aInheritedStack : private sLinkedList<Type>
{
public:
  void push(const Type& element);         //pushes element onto stack
  Type pop();                             //pops element from stack. throws error if stack empty
  Type peek();                            //peeks at element from stack (does not pop it out of the stack). throws error if stack empty
  Type& peek_rw();                        //same as peek(), but data itself can be modifiable
};

template <typename Type>
class aStack
{
  sNode<Type> *head;                      //it's sufficient, because stack is LIFO. we add to head, remove from head
public:
  aStack();
  ~aStack();

  void push(const Type& element);         //pushes element onto stack
  Type pop();                             //pops element from stack. throws error if stack empty
  Type peek();                            //peeks at element from stack (does not pop it out of the stack). throws error if stack empty
  Type& peek_rw();                        //same as peek(), but data itself can be modifiable
};

*/

template <typename Type>
class aInheritedStack : private sLinkedList<Type>
{
public:
  void push(const Type& element)
  {
    sLinkedList<Type>::Add_To_Head(element);
  }

  Type pop()
  {
    if(sLinkedList<Type>::Length() == 0)
      throw "stack empty";
   
    Type result = sLinkedList<Type>::operator[](0);
    sLinkedList<Type>::Remove_Head();
    return result;
  }

  Type peek()
  {
    if(sLinkedList<Type>::Length() == 0)
      throw "stack empty";
    return sLinkedList<Type>::operator[](0);
  }

  Type& peek_rw()
  {
    if(sLinkedList<Type>::Length() == 0)
      throw "stack empty";
    return sLinkedList<Type>::operator[](0);
  }
};

template <typename Type>
class aStack
{
  sNode<Type> *head;
public:
  aStack()
  {
    head = NULL;
  }

  ~aStack()
  {
    sNode<Type> *p;
    while(head)
    {
      p = head->next;
      delete head;
      head = p;
    }
  }

  void push(const Type& element)
  {
    sNode<Type> *p = new sNode<Type>(element);
    if(!p)
      throw "allocation problem";
    p->next = head;
    head = p;
  }

  Type pop()
  {
    if(head == NULL)
      throw "stack empty";
    
    Type result = head->data;
    sNode<Type> *p = head->next;
    delete head;
    head = p;
    return result;
  }

  Type peek()
  {
    if(head == NULL)
      throw "stack empty";
    
    return head->data;
  }

  Type& peek_rw()
  {
    if(head == NULL)
      throw "stack empty";
    
    return head->data;
  }
};
