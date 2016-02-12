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

1. For size 11:
	char array = 11 bytes
	int array = 44 bytes
	float array = 44 bytes
2. There is a difference. A char is typically 1 byte and float and int is typically 4 bytes.

 
