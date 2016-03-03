# ECE 593J - Lab 3 - Daniel Olsen
## Section 1

### Code
```c
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

                printf("Child (%d): pid = %d, time = %s\n", i, getpid(), asctime(localtime(&t)));

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
```

### Questions
* There needs to be N ```wait()``` system calls, one for each child.
* An orphan process is a child process who's parent finished its tasks before the completion of the child. A zombie process is a child process that terinated before its parent had a chance to perform a wait().

## Section 2
