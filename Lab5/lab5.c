#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

int finished;

struct node
{
	//Struct for the node of the queue
	pid_t pid;
	struct node *next;
};

struct queue
{
	//Struct for the queue
	struct node *front;
	struct node *back;

	int size;
};

void enqueue(struct queue *q, pid_t p)
{
	struct node* n = (struct node*) malloc (sizeof(struct node));

    n->pid = p;
    n->next = NULL;

    if (q->front == NULL)
	{
        q->front = n;
    } else{
        q->back->next = n;
    }

    q->back = n;
    q->size++;
}

pid_t dequeue(struct queue *q)
{
    struct node* front = q->front;
    pid_t p = front->pid;

    q->front = front->next;
    q->size--;

    free(front);
    return p;
}

void term_child()
{
	//Signal hanlder, the termination of a process
	signal(SIGCHLD, term_child);

	finished = 1;

}

int main(int argc, char const *argv[])
{
	int programCount = 0, i;
	pid_t child;
	int qt;

	struct queue q;
	q.front = NULL;
	q.back = NULL;
	q.size = 0;

	finished = 0;

	//Variable initialization
	signal(SIGCHLD, term_child);

	if(argc > 2)
	{
		qt = 1000 * atoi(&argv[1][0]); //Here you need the qt
	}
	else
	{
		printf("Usage: %s qt prog1 [prog2] ... [prog[N}\n", argv[0]);
		exit(-1);
	}

	for(programCount = 0, i = 2; i < argc; i++)
	{
		programCount++;
		//Fork, execl processes and enqueue
		printf("Message from father: Creating program %s\n", argv[i]);

		if((child = fork()) == 0)
		{
			execl(argv[i], argv[i], NULL);
		}

		enqueue(&q, child);
	}

	sleep(1);//Small safe delay

	printf("\nI am the Scheduler and I will now begin scheduling my programs:\n");

	while(q.front != NULL)//Scheduling loop
	{
		pid_t p = dequeue(&q);

		finished = 0;
		kill(p, SIGCONT);

		usleep(qt);

		if(!finished)
		{
			//send the signal SIGUSR1 to the first element in queue
			kill(p, SIGUSR1);

			usleep(1000);

			enqueue(&q, p);
		}
		else
		{
			printf("Child %d is finished\n", p);
			//remove from list
			//mark child as dead
		}
	}

	printf("All of my children finished so goodbye...\n");

	return 0;
}
