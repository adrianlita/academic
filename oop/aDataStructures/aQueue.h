#pragma once

#include "aNode.h"
#include "sLinkedList.h"

/*
aInheritedQueue definition:
  - First In First Out (LIFO)
  - a queue which is derived from a simply linked list
  - implementation is below because the use of templates

aQueue definition:
  - queue (FIFO) implementation. basically strip off everything not needed from list
  - does not inherit anything
  - does not use sentinel element as sLinkedList

template <typename Type>
class aInheritedQueue : private sLinkedList<Type>
{
public:
  void push(const Type& element);         //pushes element onto queue
  Type pop();                             //pops element from queue. throws error if queue empty
  Type peek();                            //peeks at element from queue (does not pop it out of the queue). throws error if queue empty
  Type& peek_rw();                        //same as peek(), but data itself can be modifiable
};

template <typename Type>
class aQueue
{
  sNode<Type> *head;                      //need both head and tail, as queue is FIFO. We push to tail, pop from head
  sNode<Type> *tail;                      
public:
  aQueue();
  ~aQueue();

  void push(const Type& element);         //pushes element onto queue
  Type pop();                             //pops element from queue. throws error if queue empty
  Type peek();                            //peeks at element from queue (does not pop it out of the queue). throws error if queue empty
  Type& peek_rw();                        //same as peek(), but data itself can be modifiable
};

*/

template <typename Type>
class aInheritedQueue : private sLinkedList<Type>
{
public:
  void push(const Type& element)
  {
    sLinkedList<Type>::Add_To_Tail(element);
  }

  Type pop()
  {
    if(sLinkedList<Type>::Length() == 0)
      throw "queue empty";
   
    Type result = sLinkedList<Type>::operator[](0);
    sLinkedList<Type>::Remove_Head();
    return result;
  }

  Type peek()
  {
    if(sLinkedList<Type>::Length() == 0)
      throw "queue empty";
    return sLinkedList<Type>::operator[](0);
  }

  Type& peek_rw()
  {
    if(sLinkedList<Type>::Length() == 0)
      throw "queue empty";
    return sLinkedList<Type>::operator[](0);
  }
};

template <typename Type>
class aQueue
{
  sNode<Type> *head;
  sNode<Type> *tail;
public:
  aQueue()
  {
    head = NULL;
    tail = NULL;
  }

  ~aQueue()
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
    check_if_allocated_correctly(p);
    if(tail)
      tail->next = p;
    else
      head = p;
    tail = p;
  }

  Type pop()
  {
    if(head == NULL)
      throw "stack empty";
    
    Type result = head->data;
    sNode<Type> *p = head->next;
    delete head;
    head = p;
    if(head == NULL)
      tail = NULL;
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
