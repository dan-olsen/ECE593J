#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

struct node
{
	//Struct for the node of the queue
};

struct queue
{
	//Struct for the queue
};

void enqueue()
{

}

int dequeue()
{
	
}

void termchild()
{
//Signal hanlder, the termination of a process

}

int main(int argc, char const *argv[])
{
	//Variable initialization
	signal(SIGCHLD, termchild);
	if(argc>2)
	{
		qt = 1000*atoi(&argv[1][0]);//Here you need the qt
	}
	else
	{
		printf("%s qt prog1 [prog2] ... [prog[N}\n", argv[0]);
		exit(−1);
	}
	
	
	for(...)
	{
		//Fork, execl processes and enqueue
		printf("Message from father: Creating program %s\n", argv[i]);

		if(...)
		{
			execl(argv[i], argv[i], NULL);
		}
		
		enqueue the process
	}

	sleep(1);//Small safe dealy
	printf("\nI am the Scheduler and I will now begin scheduling my programs:\n");
	
	while(queue is not empty)//Scheduling loop
	{
		send the signal SIGCONT to the first element in queue

		usleep(qt);

		if(child has not finished)
		{
			send the signal SIGUSR1 to the first element in queue
			usleep(1000);
			dequeue and re−enqueue
		}
		else
		{
			printf("A child is dead\n");
			remove from list
			mark child as dead
		}
	}
}
