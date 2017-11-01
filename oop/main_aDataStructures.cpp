#include <iostream>
#include "aDataStructures/sLinkedList.h"
using namespace std;

template class sLinkedList<int>;

int main()
{
  cout << "aDataStructures sample program" << endl;

  cout << "Simply Linked Lists" << endl;
  sLinkedList<int> a;

  a.Add_To_Tail(8);
  a.Add_To_Head(1);
  a.Add_To_Head(2);
  a.Add_To_Head(3);
  a.Add_To_Tail(4);
  a.Add_To_Tail(5);
  a.Add_To_Tail(6);
  cout << a << endl;

  a.Remove_Head();
  a.Remove_Tail();
  cout << a << endl;

  a += 18;
  a += 19;
  sLinkedList<int> b = a;
  cout << b << endl;

  a += b;
  cout << a << endl;

  a = b + 100;
  cout << a << endl;

  b = 101 + a;
  cout << b << endl;

  cout << "b[1] = " << b[1] << endl;
  b[8] = 300;
  cout << b << endl;

  cout << a << endl;
  a.Add_To_Position(105, 0);
  a.Add_To_Position(106, 2);
  a.Add_To_Position(107, 9);
  cout << a << endl;

  cout << a.Exists(106) << " " << a.Exists(501) << endl;
  
  aListSearchResult t;
  t = a.Search(100);
  cout << "100: (" << t.found << "," << t.position << ")" << endl;

  t = a.Search(8);
  cout << "8: (" << t.found << "," << t.position << ")" << endl;

  t = a.Search(30);
  cout << "30: (" << t.found << "," << t.position << ")" << endl;

  a.Remove_From_Position(0);
  cout << a << endl;
  a.Remove_From_Position(1);
  cout << a << endl;
  cout << a.Remove_From_Position(8) << " <-- "; //here you'll see 1, because it removed item from pos 8
  cout << a << endl;
  cout << a.Remove_From_Position(8) << " <-- "; //here you'll see 0, because there is no item on position 8
  cout << a << endl;

  a += 2;
  cout << a << endl;
  cout << a.Remove_First_Found(20) << " <-- ";  //here you'll see 0 because there is no 20 element
  cout << a << endl;
  cout << a.Remove_First_Found(2) << " <-- ";  //here you'll see 1 because because it erased first 2 element
  cout << a << endl;
  cout << a.Remove_First_Found(2) << " <-- ";  //here you'll see 1 because because it erased first 2 element
  cout << a << endl;
  cout << a.Remove_First_Found(2) << " <-- ";  //here you'll see 0 because there is no other 2 element
  cout << a << endl;

  cout << "aDataStructures finished!" << endl;
  return EXIT_SUCCESS;
}
