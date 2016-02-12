#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N = 0;
	char* Nc = NULL;
	int* Ni = NULL;
	float* Nf = NULL;

	int NcSize = 0;
	int NiSize = 0;
	int NfSize = 0;

	while(N <= 10)
	{
		printf("Please enter a number greater than 10: ");
		scanf("%d", &N);
	}

	NcSize = N * sizeof(char);
	NiSize = N * sizeof(int);
	NfSize = N * sizeof(float);

	printf("Size of char array: %d\n", NcSize);
	printf("Size of int array: %d\n", NiSize);
	printf("Size of float array: %d\n", NfSize);

	Nc = (char*)malloc(NcSize);

	if(Nc == NULL)
	{
		perror("ERROR: Bad malloc of char array\n");
		exit(1);
	}

        Ni = (int*)malloc(NiSize);

        if(Ni == NULL)
        {
		free(Nc);
                perror("ERROR: Bad malloc of int array\n");
                exit(1);
        }

        Nf = (float*)malloc(NfSize);

        if(Nf == NULL)
        {
		free(Nc);
		free(Ni);
                perror("ERROR: Bad malloc of float array\n");
                exit(1);
        }

	free(Nc);
	free(Ni);
	free(Nf);

	return 0;
}
