# ECE 593J - Lab 2 - Daniel Olsen
## Section 1

###Makefile:
```make
program1: input.o
	gcc -o program1 input.o

input.o: input.c
	gcc -c input.c

clean: 
	rm ./*.o
	rm ./program1
```
There are no warnings.

###Makefile:
```make
program1: input.o
	gcc -o program1 input.o

input.o: input.c
	gcc -Wall -c input.c

clean: 
	rm ./*.o
	rm ./program1
```

By adding ```-Wall``` there are now 6 warnings.

###Warnings:
```
gcc -Wall -g -c input.c
input.c: In function ‘main’:
input.c:11:2: warning: format ‘%d’ expects argument of type ‘int *’, but argument 2 has type ‘int’ [-Wformat=]
  scanf("%d", k);
  ^
input.c:12:2: warning: implicit declaration of function ‘tester’ [-Wimplicit-function-declaration]
  tester(x, k);
  ^
input.c:5:9: warning: unused variable ‘j’ [-Wunused-variable]
  int i, j, k;
         ^
input.c:13:1: warning: control reaches end of non-void function [-Wreturn-type]
 }
 ^
input.c: In function ‘tester’:
input.c:16:1: warning: control reaches end of non-void function [-Wreturn-type]
 }
 ^
input.c: In function ‘main’:
input.c:11:2: warning: ‘k’ is used uninitialized in this function [-Wuninitialized]
  scanf("%d", k);
  ^
gcc -o program1 input.o
```

The program generates a segmentation fault and does not work correctly.

###Output:
```
Segmentation fault
```

In order to debug the program we must add debug flags. This is done by adding the ```-g``` flag in the Makefile.

###Makefile:
```make
program1: input.o
	gcc -o program1 input.o

input.o: input.c
	gcc -Wall -g -c input.c

clean: 
	rm ./*.o
	rm ./program1
```

By setting a breakpoint at line 10 (after the loop) and using the continue command gdb print that the segmentation fault was in the for loop. And knowing that I was able to find that the for loop was looping 10000 times but the array had only 1000 elements.

###GDB Output:
```
Continuing.

Program received signal SIGSEGV, Segmentation fault.
0x000000000040059f in main (argc=1, argv=0x7fffffffe058) at input.c:8
8			x[i] = i;
```

Also on line number 11 the program generates a segmentation fault. This is fixed by passing ```&k``` into ```scanf()```.

###GDB Output:
```
Program received signal SIGSEGV, Segmentation fault.
0x00007ffff7a8a94a in _IO_vfscanf_internal (s=<optimized out>, 
    format=<optimized out>, argptr=argptr@entry=0x7fffffffcec8, 
    errp=errp@entry=0x0) at vfscanf.c:1826
1826	vfscanf.c: No such file or directory.
```

###Final Corrected Code:
```c
#include <stdio.h>
#include "string.h"

int main(int argc, char* argv[]) {
	int i, j, k;
	int x[1000];
	for(i = 0; i < 1000; ++i){
		x[i] = i;
	}
	printf("Enter integer in 0..9999: ");
	scanf("%d", &k);
	tester(x, k);
}
int tester(int* c, int k) {
	printf("x[%d] = %d\n", k, c[k]);
}
```

##Section 2
