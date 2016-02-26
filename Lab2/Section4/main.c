#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	FILE * f;
	int x, N, i;
	pid_t child1, child2;

	if (argc!=2)
	{
		printf("Wrong inputs\n");
		return -1;
	}
	if ((N = atoi(argv[1])) < 0)
	{
		printf("Wrong inputs\n");
		return -1;
	}

	for(i = 0; i < N; ++i)
	{
		child1 = fork();

		if(child1 < 0)
		{
			printf("Error");
			exit(1);

		}
		else if(child1 == 0)
		{
			f = fopen ("data.txt","r+");

			if (f != NULL)
			{
				fscanf(f, "%d", &x);

				printf("%d\n", x);

				x+=5;
				rewind(f);

				fprintf (f, "%d", x);
				fclose (f);
			}

			exit(0);
		}
		child2 = fork();

		if(child2 < 0)
		{
			printf("Error");
			exit(1);

		}
		else if(child2 == 0)
		{
			sleep(1);
			f = fopen ("data.txt","r+");

			if (f != NULL)
			{
				fscanf(f, "%d", &x);

				printf("%d\n", x);

				x+=10;
				rewind(f);

				fprintf (f, "%d", x);
				fclose (f);
			}

			exit(0);
		}
		sleep(2);
	}

	int status;
	for (i = 0; i < N; ++i)
	{
				wait(&status);
	}

	return 0;
}
