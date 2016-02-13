# ECE 593J - Lab 1 - Daniel Olsen
## Section 1

Privilege rights for "ECE_593":
```
drwxrwx---   2 dolsen eegrad 2 Feb  5 17:16 ECE_593
```

Privilege rights for "exercise1":
```
drwxrwx--- 2 dolsen eegrad 2 Feb  5 17:19 exercise1
```

Original privilege rights for "code1":
```
-rw-rw---- 1 dolsen eegrad 0 Feb  5 17:21 code1
```
Privilege rights after execution rights were added:
```
-rwxrwx--- 1 dolsen eegrad 0 Feb  5 17:21 code1
```

There is something wrong. The file is empty and the terminal does not know how to execute it.

## Section 2

Changes needed to given code:

1. Need to add the stdio library in order to use `printf()`
```c
#include <stdio.h>
```

The program does not produce the correct result. The `%d` for the `sqrt` result needs to be `%f` because `sqrt` returns a double not an int.

To fix the remaining errors add `int` in front of main and `return 0` at end of main function.

Corrected code:
```c
#include <math.h>
#include <stdio.h>

int main()
{
	int i;

	printf("\t Number \t\t Square Root of Number\n\n");

	for (i=0; i<=360; ++i)
		printf("\t %d \t\t\t %f \n",i, sqrt(i));

	return 0;
}
```

## Section 3

Code:
```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N = 0;
	char* Nc = NULL;
	int* Ni = NULL;
	float* Nf = NULL;

	int NcSize = 0;
	int NiSize = 0;
	int NfSize = 0;

	while(N <= 10)
	{
		printf("Please enter a number greater than 10: ");
		scanf("%d", &N);
	}

	NcSize = N * sizeof(char);
	NiSize = N * sizeof(int);
	NfSize = N * sizeof(float);

	printf("Size of char array: %d\n", NcSize);
	printf("Size of int array: %d\n", NiSize);
	printf("Size of float array: %d\n", NfSize);

	Nc = (char*)malloc(NcSize);

	if(Nc == NULL)
	{
		perror("ERROR: Bad malloc of char array\n");
		exit(1);
	}

        Ni = (int*)malloc(NiSize);

        if(Ni == NULL)
        {
		free(Nc);
                perror("ERROR: Bad malloc of int array\n");
                exit(1);
        }

        Nf = (float*)malloc(NfSize);

        if(Nf == NULL)
        {
		free(Nc);
		free(Ni);
                perror("ERROR: Bad malloc of float array\n");
                exit(1);
        }

	free(Nc);
	free(Ni);
	free(Nf);

	return 0;
}
```

Commands used to compile:
```
gcc ./code2.c -o myprogram
```

```
gcc -c ./code2.c
gcc ./code2.o -o myprogram
```

For size  N = 11

Data Type | Bytes |
--- | --- |
`char` | 11 |
`int` | 44 |
`float` | 44 |

There is a difference. A `char` is typically 1 byte and `float` and `int` is typically 4 bytes. So 11 `char` would be 11 bytes and 11 `int` would be 44 bytes.

## Section 4


There are warnings. The types of `char_pointer = int_array` and `int_pointer = char_array` are incompatible. Also, the output is wrong.

Changing the following lines will remove the warnings and correct the output.
```c
char_pointer = int_array;
int_pointer = char_array;
```
to
```c
char_pointer = (char*) int_array;
int_pointer = (int*) char_array;
```
and
```c
int_pointer = int_pointer + 1;
```
to
```c
int_pointer = (int*)((char*)int_pointer + 1);
```
and
```c
char_pointer = char_pointer + 1;
```
to 
```c
char_pointer = (char*)((int*)char_pointer + 1);
```

Before the changes were made the first loop printed addresses that differed by 4 bytes because the `int*` was being increased by 4 bytes or the size of 1 `int`. And the second loop printed addresses that differed by 1 byte because the `char*` was being increased by 1 byte or the size of 1 `char`. The pointer arithmetic was increasing the pointer by the same type of the pointer instead of the type the pointer points to.

Corrected code:
```c
#include<stdio.h>

int main(){

  int i;
  char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
  int int_array[5] = {1, 2, 3, 4, 5};

  char *char_pointer;
  int *int_pointer;

  char_pointer = (char*) int_array;
  int_pointer = (int*) char_array;

  for(i=0; i < 5; i++) {
    printf("[Integer pointer] points to %p, which contains the char '%c'\n", int_pointer, *int_pointer);
    int_pointer = (int*)((char*)int_pointer + 1);
  }

  for(i=0; i < 5; i++) {
    printf("[Char pointer] points to %p, which contains the integer '%d'\n", char_pointer, *char_pointer);
    char_pointer = (char*)((int*)char_pointer + 1);
  }

}
```

## Section 5

Code for `void*`:
```c
#include<stdio.h>

int main(){

  int i;
  char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
  int int_array[5] = {1, 2, 3, 4, 5};

  void *pointer;

  pointer = char_array;

  for(i=0; i < 5; i++) {
    printf("[Integer pointer] points to %p, which contains the char '%c'\n", pointer, *(char*)pointer);
    pointer = (char*)pointer + 1;
  }

  pointer = int_array;

  for(i=0; i < 5; i++) {
    printf("[Char pointer] points to %p, which contains the integer '%d'\n", pointer, *(int*)pointer);
    pointer = (int*)pointer + 1;
  }

}
```

Code for `unsigned int*`:

```c
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
```

The `void*` is the more appropriate solution because this is what `void*` are meant to do and the `unsigned int*` requires more type casting.
