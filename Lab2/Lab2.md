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
###Code
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int N = 0;
	int i;
	pid_t child;
	
	printf("Enter number greater than 10: ");
	scanf("%d", &N);
	
	if(N > 10)
	{

		for(i = 0; i < N; ++i)
		{
			child = fork();

			if(child < 0)
			{
        			printf("Error");
        			exit(1);

			} else if(child == 0)
			{
				time_t t = time(NULL);
				
				printf("Child (%d): pid = %d, time = %s\n", i, getpid(), asctime(localtime(&t)));
				
				exit(0);
			}
		}

		printf("Parent: pid = %d\n", getpid());
		
		int status;
		for (i = 0; i < N; ++i)
		{
    			wait(&status);
		}
	}

	return 0;
}
```

###Sample Output
```
Enter number greater than 10: 11
Child (0): pid = 10348, time = Fri Feb 26 15:55:15 2016
Child (1): pid = 10349, time = Fri Feb 26 15:55:15 2016
Child (2): pid = 10350, time = Fri Feb 26 15:55:15 2016
Child (3): pid = 10351, time = Fri Feb 26 15:55:15 2016
Child (4): pid = 10352, time = Fri Feb 26 15:55:15 2016
Child (5): pid = 10353, time = Fri Feb 26 15:55:15 2016
Child (6): pid = 10354, time = Fri Feb 26 15:55:15 2016
Child (7): pid = 10355, time = Fri Feb 26 15:55:15 2016
Child (8): pid = 10356, time = Fri Feb 26 15:55:15 2016
Child (9): pid = 10357, time = Fri Feb 26 15:55:15 2016
Child (10): pid = 10358, time = Fri Feb 26 15:55:15 2016
Parent: pid = 10343
```

The pid's are different and the time is dirrent. The OS chooses free pid's to assign the new processes. 

The maximum number of processes that linux supports by default is 32768 and more specifically the `ulimit` system limits a given user to 31115 processes. 

###Commands Used
```bash
dolsen@engEE-e121-Dxx ~/Git/ECE593J/Lab2/Section2 $ ulimit -u
31115
dolsen@engEE-e121-Dxx ~/Git/ECE593J/Lab2/Section2 $ cat /proc/sys/kernel/pid_max
32768
```

As the program is now the maximum can never be hit because if we spawn 40,000 processes the processes that are spawned first will exit before the last ones are created.

###Makefile
```make
program1: main.o
	gcc -o program2 main.o

input.o: main.c
	gcc -Wall -g -c main.c

clean: 
	rm ./*.o
	rm ./program2
```

##Section 3
