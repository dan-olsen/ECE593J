#include<stdio.h>

int main(){

  int i;
  char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
  int int_array[5] = {1, 2, 3, 4, 5};

  unsigned int *pointer;

  pointer = (unsigned int*)char_array;

  for(i=0; i < 5; i++) {
    printf("[Integer pointer] points to %p, which contains the char '%c'\n", pointer, *pointer);
    pointer = (unsigned int*)((char*)pointer + 1);
  }

  pointer = (unsigned int*)int_array;

  for(i=0; i < 5; i++) {
    printf("[Char pointer] points to %p, which contains the integer '%d'\n", pointer, *pointer);
    pointer = (unsigned int*)((int*)pointer + 1);
  }

}
