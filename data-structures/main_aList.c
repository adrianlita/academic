#include <stdlib.h>
#include <stdio.h>
#include "aList/aList.h"

int main()
{

  aList list;
  aList_Init(&list, 5);

  aList_Add_Head(&list, 1);
  aList_Add_Head(&list, 2);
  aList_Add_Head(&list, 3);
  aList_Add_Tail(&list, 4);
  aList_Add_Tail(&list, 5);
  aList_Add_Tail(&list, 6);

  for(int i = 0; i < list.n; i++)
    printf("%d ", list.data[i]);
  printf("\n");

  aList_Remove_Tail(&list);

  for(int i = 0; i < list.n; i++)
    printf("%d ", list.data[i]);
  printf("\n");

  aList_Remove_Head(&list);

  for(int i = 0; i < list.n; i++)
    printf("%d ", list.data[i]);
  printf("\n");

  aList_Remove_Element(&list, 4);

  for(int i = 0; i < list.n; i++)
    printf("%d ", list.data[i]);
  printf("\n");
  


  return EXIT_SUCCESS;
}
