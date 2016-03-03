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

