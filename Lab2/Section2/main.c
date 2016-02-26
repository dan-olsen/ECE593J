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

				printf("Child (%d): pid = %d, time = %s", i, getpid(), asctime(localtime(&t)));

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
