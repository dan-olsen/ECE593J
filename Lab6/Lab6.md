# ECE 593J - Lab 6 - Daniel Olsen
## Modified Code
### `threaded_task`
```c
void *threaded_task(void *t) {
  // The sub-routine called by each thread
  long id;
  id = (long)t;
  printf("Task %ld started\n", id);
  int i;
  double result = 0.0;
  for (i = 0; i < 1000000; i++) {
    result = result + sin(i) * tan(i);
  }
  printf("Task %ld completed with result %e\n", id, result);
  pthread_exit((void*) t);
}
```
### `parallel`
```c
void *parallel(int num_tasks)
{
  //here you create threads
  long i = 0;
  int r;
  void *status;
  pthread_attr_t attr;
  pthread_t threads[MAX_NUM_THREADS];

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(i = 0; i < num_tasks; i++)
  {
    r = pthread_create(&threads[i], &attr, threaded_task, (void *)i);
    
    if (r) {
      printf("ERROR; return code from pthread_create() is %d\n", r);
      exit(-1);
    }
  }

  pthread_attr_destroy(&attr);

  for(i = 0; i < num_tasks; i++)
  {
    r = pthread_join(threads[i], &status);

    if (r) {
      printf("ERROR; return code from pthread_join() is %d\n", r);
      exit(-1);
    }
  }
}
```
## Timing Results
| Mode     | # of Tasks | Real Time | User Time | System Time |
|:--------:|:----------:|:---------:|:---------:|:-----------:|
| Serial   | 1          | 0m0.134s  | 0m0.132s  | 0m0.000s    |
| Parallel | 1          | 0m0.129s  | 0m0.132s  | 0m0.000s    |
| Serial   | 2          | 0m0.229s  | 0m0.224s  | 0m0.000s    |
| Parallel | 2          | 0m0.139s  | 0m0.272s  | 0m0.000s    |
| Serial   | 10         | 0m0.826s  | 0m0.820s  | 0m0.000s    |
| Parallel | 10         | 0m0.287s  | 0m1.060s  | 0m0.000s    |
| Serial   | 20         | 0m1.608s  | 0m1.600s  | 0m0.000s    |
| Parallel | 20         | 0m0.476s  | 0m1.808s  | 0m0.004s    |
| Serial   | 40         | 0m3.105s  | 0m3.084s  | 0m0.000s    |
| Parallel | 40         | 0m0.891s  | 0m3.404s  | 0m0.004s    |
| Serial   | 80         | 0m6.075s  | 0m6.048s  | 0m0.000s    |
| Parallel | 80         | 0m1.742s  | 0m6.708s  | 0m0.000s    |
| Serial   | 160        | 0m12.058s | 0m12.008s | 0m0.000s    |
| Parallel | 160        | 0m3.368s  | 0m13.088s | 0m0.004s    |
| Serial   | 200        | 0m15.174s | 0m15.112s | 0m0.000s    |
| Parallel | 200        | 0m4.180s  | 0m16.240s | 0m0.000s    |

The parallel version saw significant speedups compared to the serial version starting after just 2 tasks. The maximum speedup observed was 3.6. 

The reason the user time measurements are higher than the real time for the parallel version is because the time command sums up all user time in all cores. Since the parallel version is multithreaded and runs on multiple cores the real time can exceed the real time.

## Complete Code
```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NUM_THREADS 200

/* A task that takes some time to complete. The id identifies distinct
   tasks for printed messages. */
void *task(int id) {
  printf("Task %d started\n", id);
  int i;
  double result = 0.0;
  for (i = 0; i < 1000000; i++) {
    result = result + sin(i) * tan(i);
  }
  printf("Task %d completed with result %e\n", id, result);
}

/* Same as 'task', but meant to be called from different threads. */
void *threaded_task(void *t) {
  // The sub-routine called by each thread
  long id;
  id = (long)t;
  printf("Task %ld started\n", id);
  int i;
  double result = 0.0;
  for (i = 0; i < 1000000; i++) {
    result = result + sin(i) * tan(i);
  }
  printf("Task %ld completed with result %e\n", id, result);
  pthread_exit((void*) t);
}

/* Run 'task' num_tasks times serially. */
void *serial(int num_tasks) {
  int i;
  for (i = 0; i < num_tasks; i++) {
    task(i);
  }
}

/* Run 'task' num_tasks times, creating a separate thread for each
   call to 'task'. */
void *parallel(int num_tasks)
{
  //here you create threads
  long i = 0;
  int r;
  void *status;

  pthread_attr_t attr;
  pthread_t threads[MAX_NUM_THREADS];

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(i = 0; i < num_tasks; i++)
  {
    r = pthread_create(&threads[i], &attr, threaded_task, (void *)i);
    
    if (r) {
      printf("ERROR; return code from pthread_create() is %d\n", r);
      exit(-1);
    }
  }

  pthread_attr_destroy(&attr);

  for(i = 0; i < num_tasks; i++)
  {
    r = pthread_join(threads[i], &status);

    if (r) {
      printf("ERROR; return code from pthread_join() is %d\n", r);
      exit(-1);
    }
  }
}

void *print_usage(int argc, char *argv[]) {
  printf("Usage: %s serial|parallel num_tasks\n", argv[0]);
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {print_usage(argc, argv);}

  int num_tasks = atoi(argv[2]);

  if (!strcmp(argv[1], "serial")) {
    serial(num_tasks);
  } else if (!strcmp(argv[1], "parallel")) {
    parallel(num_tasks);
  }
  else {
    print_usage(argc, argv);
  }

  printf("Main completed\n");
  pthread_exit(NULL);
}
```
