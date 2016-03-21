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

