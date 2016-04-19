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
