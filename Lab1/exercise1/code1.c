#include <math.h>
#include <stdio.h>

int main()
{
	int i;

	printf("\t Number \t\t Square Root of Number\n\n");

	for (i=0; i<=360; ++i)
		printf("\t %d \t\t\t %f \n",i, sqrt(i));

	return 0;
}
