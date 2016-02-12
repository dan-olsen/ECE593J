# ECE 593J - Lab 1 - Daniel Olsen
## Section 1

Privilege rights for "ECE_593":
```
drwxrwx---   2 dolsen eegrad             2 Feb  5 17:16 ECE_593
```

Privilege rights for "exercise1":
```
drwxrwx---  2 dolsen eegrad    2 Feb  5 17:19 exercise1
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

1. Need to add the stdio library inorder to use `printf()`
```c
#include <stdio.h>
```

The program does not produce the correct result. The `%d` for the sqrt result needs to be `%f` because sqrt returns a double not an int.

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





