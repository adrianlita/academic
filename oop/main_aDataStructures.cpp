#include <iostream>
#include "aDataStructures/sLinkedList.h"
#include "aDataStructures/dLinkedList.h"
using namespace std;

int main()
{
  cout << "aDataStructures sample program" << endl;
  
  aListSearchResult t;

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

  cout << endl << endl << endl;

  cout << "Doubly Linked Lists" << endl;
  dLinkedList<int> ad;

  ad.Add_To_Tail(8);
  ad.Add_To_Head(1);
  ad.Add_To_Head(2);
  ad.Add_To_Head(3);
  ad.Add_To_Tail(4);
  ad.Add_To_Tail(5);
  ad.Add_To_Tail(6);
  cout << ad << endl;

  ad.Remove_Head();
  ad.Remove_Tail();
  cout << ad << endl;

  ad += 18;
  ad += 19;
  dLinkedList<int> bd = ad;
  cout << bd << endl;

  ad += bd;
  cout << ad << endl;

  ad = bd + 100;
  cout << ad << endl;

  bd = 101 + ad;
  cout << bd << endl;

  cout << "bd[1] = " << bd[1] << endl;
  bd[8] = 300;
  cout << bd << endl;

  cout << ad << endl;
  ad.Add_To_Position(105, 0);
  ad.Add_To_Position(106, 2);
  ad.Add_To_Position(107, 9);
  cout << ad << endl;

  t = ad.Search_From_Head(100);
  cout << "100: (" << t.found << "," << t.position << ")" << endl;

  t = ad.Search_From_Tail(100);
  cout << "100: (" << t.found << "," << t.position << ")" << endl;

  t = ad.Search_From_Head(8);
  cout << "8: (" << t.found << "," << t.position << ")" << endl;

  t = ad.Search_From_Head(30);
  cout << "30: (" << t.found << "," << t.position << ")" << endl;

  ad.Remove_From_Position(0);
  cout << ad << endl;
  ad.Remove_From_Position(1);
  cout << ad << endl;
  cout << ad.Remove_From_Position(8) << " <-- "; //here you'll see 1, because it removed item from pos 8
  cout << ad << endl;
  cout << ad.Remove_From_Position(8) << " <-- "; //here you'll see 0, because there is no item on position 8
  cout << ad << endl;

  cout << "Head->Tail: " << ad << endl;
  ad.Set_Run_Direction(true);
  cout << "Tail->Head: " << ad << endl;

  //now play with current element
  cout << "Going with current element from 0 to 15 (if exists)" << endl;
  ad.Set_Current_Element_Position(0);
  for(int i = 0; i < 15; i++)
  {
    cout << ad.Current_Element() << "(pos=" << ad.Get_Current_Element_Position() << ") ";
    ++ad;
  }
  cout << endl;
  cout << "Going with current element back for 15 positions (if exist))" << endl;
  for(int i = 0; i < 15; i++)
  {
    cout << ad.Current_Element() << "(pos=" << ad.Get_Current_Element_Position() << ") ";
    --ad;
  }

  cout << endl;
  
  cout << "aDataStructures finished!" << endl;
  return EXIT_SUCCESS;
}
