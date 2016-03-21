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

### Questions
Child 1 does not know the PID of child 2 so for child 1 to send a signal to child 2 it would have to first signal the parent who would then signal child 2. There is an issue here if the parent dies before child 1 sends its signal child 2 will never recieve the signal.

You would use the same idea as before however before child 1 forks the parent's PID would need to be stored in a variable the new child would inherit.

## Section 2
