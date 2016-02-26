#include <stdio.h>

int main(int argc, char* argv[])
{
	FILE * f;
	int x, N, i;

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
	}

	return 0;
}
