# Object-Oriented Programming examples in **C++**
---
# aMatrix
## Implementing a 2D matrix in C++.

The requirements for implemeting the 2-dimensional matrix class in C++ are the following:
  * class name is aMatrix
  * base type for the matrix will be real numbers (double)
  * exceptions thrown if operation is not possible
  * basic matrix <-> double operations (+ - * /)
  * basic matrix <-> matrix operations (+ - * /)  when possible
  * determinant calculation
  * matrix inverse calculation
  * basic default matrix (O and I)

---
# aString
## Implementing a simple string in C++ without using the String class.

Please note that this class does not use the C-string library.
It uses a custom designed string-manipuating library, written specially so we can go into detail with everything.
You can find in in **utils/my_string.h**.

The requirements for implemeting a string in C++, without using the String class:
  * class name is aString
  * base type for the string will be a variable-size char array
  * always maintaining the least possbile ammount of memory occupied
  * exceptions thrown on operations which are not possible
  * coverting to and from char* or const char*
  * basic string operations: set, concatenate
  * string comparison
  * element-wise access

---
# aBigNum
## Big numbers implementation in C++

Sample implementation of big numbers (big integers) in C++, with C++ operator overloading and having most of the integer operations functional for any-size integers. Memory size and code efficiency haven't been cared for in this implementation. Base is **10** and it is fixed.

Implementations of aBigNum class:
  * constructors, destructor, copy operators (from int, and from char*)
  * ostream operator<< overloaded to display easily using cout
  * standard operations: + - * /(div) and %(modulo)
  * ++ and -- operators
  * negativization
  * comparison operations (all)

---
# aDataStructures
Simple data structures examples implemented in C++. All of the structures here are templated.

## Linked List and Doubly Linked List

Both the simply linked list and the doubly linked list are implemented using sentinel element, for simplicity and code efficiency.
On the doubly linked list, whenever a certain position is looked for the function decides automatically if it starts at head or at tail (whichever is closer).

Implementation of linked lists:
  * head and tail
  * add element to: head, tail or position
  * remove element from: head, tail, position or look for element
  * operator[] - use list as an array
  * search for element
  * have a state (current position) manipulable throughout the list (only the doubly linked list)

## Stack and Queue

Stack and queue are implemented in to ways, both with the same prototype:
  * derived from sLinkedList
  * written from scratch, more efficiently than derived from sLinkedList

Stack and queue implementation features:
  * push function / adding element to the stack or queue
  * pop function / extracting element fromt he stack or queue
  * peek function / looking at the element to be popped, without popping it

## Binary Search Tree, AVL Balanced Binary Search Tree

Binary search tree features:
  * adding an element
  * deleteing an element
  * counting elements
  * deleting whole tree
  * check if element exists
  * in-, pre- and post-order tree traversals

AVL trees are inherited from binary search trees. Their main advantage is that they are balanced ( |height(right) - height(left)| < 2 ).
AVL trees have the following differences from the base class Binary Search Trees:
  * node rotations (simple left, simple right, double left, double right)
  * balance function
  * node class is derived from base class' node class (tNodeAVL<Type> is derived from tNode<Type>)

---
# aPolygon
A simple convex, non-intersecting polygon for demonstrating class inheritance and polymorphism.

The base class include:
  * base constructors and destructor
  * outputing to ostream
  * perimeter calculation function
  * pure virtual function for area which results in
  * abstractization of class aPolygon

Derived classes are:
  * aTriangle: public aPolygon
  * aRectangle: public aPolygon
  * aSquare: public aRectangle

In all the derived classes we implement extra functions, specific to those classes, but we also re-implement the Perimeter() function in order to make it as efficient as possible (and of course, in order to show how polymorphism and virtual functions work).
