# ECE 593J - Lab 3 - Daniel Olsen
## Section 1

### Code
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

### Questions
* There needs to be N ```wait()``` system calls, one for each child.
* An orphan process is a child process who's parent finished its tasks before the completion of the child. A zombie process is a child process that terinated before its parent had a chance to perform a wait().

## Section 2

### Code
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

static const char* const usage_template = 
    "Usage: %s N\n"
    "\tN: integer > 10\n";
   
void child_function(int child_num, int lower_bound, int upper_bound);

int main(int argc, char* argv[])
{
	int N;
	pid_t child1, child2, child3;
	
	if (argc != 2)
	{
		printf (usage_template, argv[0]);
		
		return -1;
	}
	
	if ((N = atoi(argv[1])) <= 10)
	{
		printf (usage_template, argv[0]);
		
		return -1;
	}
	
	if((child1 = fork()) == 0)
	{
		//Child 1
		child_function(1, 0, N/3);
		
	}
	
	if((child2 = fork()) == 0)
	{
		//Child 2
		child_function(2, N/3, (2* N)/3);
		
	}
	
	if((child3 = fork()) == 0)
	{
		//Child 3
		child_function(3, (2 * N)/3, N);
		
	}
	
	sleep(5);
	
	kill(child1, SIGKILL);
	kill(child2, SIGKILL);
	kill(child3, SIGKILL);

	return 0;
}

void child_function(int child_num, int lower_bound, int upper_bound)
{
	int i = 0;
	
	while(1)
	{
		for(i = lower_bound; i < upper_bound; ++i)
		{
			printf("Child %d (%d): %d\n", child_num, getpid(), i);
		}
	}
}
```

### Makefile
```make
program2: lab3-section2.o
	gcc -o program2 lab3-section2.o

lab3-section2.o: lab3-section2.c
	gcc -Wall -g -c lab3-section2.c

clean: 
	rm ./*.o
	rm ./program2
```

##Section 3
