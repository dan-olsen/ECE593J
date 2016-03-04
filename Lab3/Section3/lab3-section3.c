#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

static const char* const usage_template = 
    "Usage: %s N [program]\n";

void on_alarm();

int pid;

int main(int argc, char* argv[])
{
	int sec, status;
	char* prog = NULL;
	char* args[2];
	
	if (argc < 3)
	{
		printf (usage_template, argv[0]);
		
		return -1;
	}
	
	if ((sec = atoi(argv[1])) <= 0)
	{
		printf (usage_template, argv[0]);
		
		return -1;
	}
	
	prog = argv[2];
	
	args[0] = argv[2];
	args[1] = NULL;
	
	
	if((pid = fork()) == 0)
	{
		execvp(prog, args);
		
	} else if (pid < 0) {
		printf("Failed to fork\n");
		
		return -1;
	} else {
		signal(SIGALRM, on_alarm);
	
		printf("Now I wait\n");
	
		alarm(sec);
	
		if (wait(&status) == -1)
		{
			printf("Something bad happened to child\n");
		}
		
		printf("Done waiting\n");
	}

	return 0;
}

void on_alarm()
{
	printf("Killing child\n");
	
	kill(pid, SIGKILL);
}

