#include "aList.h"
#include "../utils/utils.h"
#include <stdlib.h>

static void aList_manage_memory(aList* this, const unsigned int desired_size)
{
  if(this == NULL)
    return;

  unsigned int new_size;

  if(desired_size < this->mem_size)
  {
    if(this->mem_size - desired_size <= this->mem_chunk_size)
    {
      if(desired_size == 0)
      {
        this->mem_size = 0;
        free(this->data);
        this->data = NULL;
        return;
      }

      new_size = desired_size;
      if(desired_size % this->mem_chunk_size != 0)
        new_size += (this->mem_chunk_size - desired_size % this->mem_chunk_size);
      
      DATA *buf = (DATA*)malloc(new_size * sizeof(DATA));
      check_if_allocated_correctly(buf);
      for(unsigned int i = 0; i < desired_size; i++)
        buf[i] = this->data[i];
      free(this->data);
      this->data = buf;
      this->mem_size = new_size;
    }
  }
  else
  if(desired_size > this->mem_size)
  {
    new_size = desired_size;
    if(desired_size % this->mem_chunk_size != 0)
      new_size += (this->mem_chunk_size - desired_size % this->mem_chunk_size);
    DATA *buf = (DATA*)malloc(new_size * sizeof(DATA));
    check_if_allocated_correctly(buf);
    for(unsigned int i = 0; i < this->mem_size; i++)
      buf[i] = this->data[i];
    free(this->data);
    this->data = buf;
    this->mem_size = new_size;
  }
}

void aList_Init(aList* this, const unsigned int chunk_size)
{
  if(this == NULL)
    return;

  this->data = NULL;
  this->n = 0;
  this->mem_size = 0;
  this->mem_chunk_size = chunk_size;
}

int aList_Add_Head(aList* this, const DATA data)
{
  if(this == NULL)
    return -1;

  this->n++;
  aList_manage_memory(this, this->n);
  
  //move everything to the left
  for(int i = this->n - 1; i >= 1; i--)
    this->data[i] = this->data[i - 1];
  
  this->data[0] = data;
}

int aList_Add_Tail(aList* this, const DATA data)
{
  if(this == NULL)
    return -1;

  this->n++;
  aList_manage_memory(this, this->n);

  this->data[this->n - 1] = data;
  my_assert("salut");
}

int aList_Add_Position(aList* this, const DATA data, const unsigned int position)
{
  if(this == NULL)
    return -1;

}

int aList_Remove_Head(aList* this)
{
  if(this == NULL)
    return -1;

  for(unsigned int i = 0; i < this->n - 1; i++)
    this->data[i] = this->data[i + 1];
  this->n--;
  aList_manage_memory(this, this->n);
}

int aList_Remove_Tail(aList* this)
{
  if(this == NULL)
    return -1;

  this->n--;
  aList_manage_memory(this, this->n);
}

int aList_Remove_Element(aList* this, const DATA data)
{
  if(this == NULL)
    return -1;

  this->n--;
  aList_manage_memory(this, this->n);
}

int aList_Remove_Position(aList* this, const unsigned int position)
{
  if(this == NULL)
    return -1;
  
  
}

int aList_Find(aList* this, const DATA data)
{
  if(this == NULL)
    return -1;

  for(int i = 0; i < this->n; i++)
  {
    if(this->data[i] == data)
      return i;
  }

  return -1;
}

int aList_Set(aList* this, const unsigned int position, const DATA data)
{
  if(this == NULL)
    return -1;

}

int aList_Get(aList* this, const unsigned int position, DATA* data)
{
  if(this == NULL)
    return -1;

}

