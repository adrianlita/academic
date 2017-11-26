#pragma once

typedef int DATA;

typedef struct
{
  DATA *data;
  unsigned int n;                 //number of items in LIST

  unsigned int mem_size;          //number of allocated items in *data
  unsigned int mem_chunk_size;    //minimum number of items to allocate
} aList;

void aList_Init(aList* this, const unsigned int chunk_size);
int aList_Add_Head(aList* this, const DATA data);
int aList_Add_Tail(aList* this, const DATA data);
int aList_Add_Position(aList* this, const DATA data, const unsigned int position);

int aList_Remove_Head(aList* this);
int aList_Remove_Tail(aList* this);
int aList_Remove_Element(aList* this, const DATA data);
int aList_Remove_Position(aList* this, const unsigned int position);

int aList_Find(aList* this, const DATA data);
int aList_Set(aList* this, const unsigned int position, const DATA data);
int aList_Get(aList* this, const unsigned int position, DATA* data);
