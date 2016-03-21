# ECE 593J - Lab 4 - Daniel Olsen
## Section 1
### Code
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void child_signal_handler();
	
int main(int argc, char* argv[])
{
	int info;
	pid_t child1, child2;
	
	signal(SIGINT, child_signal_handler); 
	
	if((child1 = fork()) == 0)
	{
		//Child 1
		printf("Child 1: Executing \"ls /home/\"\n");
		system("ls /home/");
		pause();
		
	}
	
	if((child2 = fork()) == 0)
	{
		//Child 2
		printf("Child 2: Executing \"mkdir new\"\n");
		system("mkdir new");
		pause();
		
	}
	
	sleep(5);
	
	kill(child1, SIGINT);		
	kill(child2, SIGINT);

	wait(&info);
	wait(&info);
	
	return 0;
}

void child_signal_handler()
{
	printf("Child PID: %d Parent PID: %d\n", getpid(), getppid());

	exit(0);
}
```

###Makefile
```make
program1: lab4-section1.o
	gcc -o program1 lab4-section1.o

lab4-section1.o: lab4-section1.c
	gcc -Wall -g -c lab4-section1.c

clean: 
	rm ./*.o
	rm ./program1
```
### Questions
Child 1 does not know the PID of child 2 so for child 1 to send a signal to child 2 it would have to first signal the parent who would then signal child 2. There is an issue here if the parent dies before child 1 sends its signal child 2 will never recieve the signal.

You would use the same idea as before however before child 1 forks the parent's PID would need to be stored in a variable the new child would inherit.

## Section 2
###Code
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

static const char* const usage_template = 
    "Usage: %s N\n"
    "\tN: integer > 10\n";
   
void child_function(int child_num, int lower_bound, int upper_bound);

void child1_signal_handler();
void child2_signal_handler();
void child3_signal_handler();

void parent_singal_handler();

int N;
	
int main(int argc, char* argv[])
{
	int info;
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
		signal(SIGUSR1, child1_signal_handler); 

		pause();
		
	}
	
	if((child2 = fork()) == 0)
	{
		//Child 2
		signal(SIGUSR1, child2_signal_handler);

		pause();
		
	}
	
	if((child3 = fork()) == 0)
	{
		//Child 3
		signal(SIGUSR1, child3_signal_handler);

		pause();
		
	}
	
	signal(SIGUSR2, parent_singal_handler);
	
	sleep(5);
	
	kill(child1, SIGUSR1);
	pause();
		
	kill(child2, SIGUSR1);
	pause();
	
	kill(child3, SIGUSR1);
	pause();
	
	wait(&info);
	wait(&info);
	wait(&info);

	return 0;
}

void child_function(int child_num, int lower_bound, int upper_bound)
{
	int i = 0;
	
	for(i = lower_bound; i < upper_bound; ++i)
	{
		printf("Child %d (%d): %d\n", child_num, getpid(), i);
	}

}

void child1_signal_handler()
{
	child_function(1, 0, N/3);
	
	kill(getppid(), SIGUSR2);

	exit(0);
}

void child2_signal_handler()
{
	child_function(2, N/3, (2* N)/3);
	
	kill(getppid(), SIGUSR2);
	
	exit(0);
}

void child3_signal_handler()
{
	child_function(3, (2 * N)/3, N);
	
	kill(getppid(), SIGUSR2);

	exit(0);
}

void parent_singal_handler()
{
	signal(SIGUSR2, parent_singal_handler);
}
```

###Questions
There could be an issue that could lead to a signal being dropped. Because the signal handlers are set up in the children the parent needs to sleep before signaling the first child. This sleep does not guarantee that the signal handlers have been set up in the children when the parent sends the first signal. If the handlers are not set up the children will just terminate (default action for SIGUSR1) and the parent will not recieve the response from child 1 and will wait forever.
