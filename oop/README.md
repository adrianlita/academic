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

